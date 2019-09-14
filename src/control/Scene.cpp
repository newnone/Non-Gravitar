// MIT License
//
// Copyright (c) 2018 Oscar B. et al.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <utility>
#include "Scene.hpp"
#include "shape-group/CollisionGroup.hpp"
#include "shape/MountainChain.hpp"
#include "shape/Planet.hpp"

using type_index = std::type_index;


namespace gvt {
	TypeVertex::TypeVertex (std::type_index type):
			Vertex(type.hash_code(), std::make_shared<type_index>(type)) {
	}

	bool TypeVertex::operator== (TypeVertex const &other) const {
		return  mId == other.mId &&
				mValue->hash_code() == other.mValue->hash_code();
	}


	Scene::Scene(Vectord size, shared_ptr<ShapeGroup> shapes):
			mSize{size}, mShapes{std::move(shapes)} {
		mShapesView.reset(new ShapeGroupView(mShapes));
		auto _1 = std::placeholders::_1;

		initializeDestroyGraph();
		mDestroyCallback = mShapes->addCallback(
			std::bind(&Scene::onCollisionOccurred, this, _1)
		);
	}

	Scene::~Scene() {
		mShapes->removeCallback(mDestroyCallback);
	}

	void Scene::initializeDestroyGraph() {
		// Edges to ba later added to the graph. Each (u, v) edge says that,
		// if a shape of type u clashes with a shape of type v, then this last
		// one is destroyed.
		std::vector<std::pair<type_index, type_index>> destroyPair = {
			{typeid(Bunker), typeid(Spaceship)},
			{typeid(RoundMissile), typeid(Spaceship)},
			{typeid(MountainChain), typeid(Spaceship)},

			{typeid(RoundMissile), typeid(Bunker)},

			{typeid(Spaceship), typeid(RoundMissile)},
			{typeid(Bunker), typeid(RoundMissile)},
			{typeid(MountainChain), typeid(RoundMissile)},
			{typeid(Planet), typeid(RoundMissile)},
		};

		for (auto const &pair: destroyPair) {
			// Insert vertices, irrespective of whether they are present or not
			mDestroyGraph.insertVertex(TypeVertex(pair.first));
			mDestroyGraph.insertVertex(TypeVertex(pair.second));

			mDestroyGraph.insertEdge(
					TypeVertex(pair.first), TypeVertex(pair.second)
			);
		}
	}

	void Scene::onCollisionOccurred (shared_ptr<gvt::Event> const &e) {
		auto collision = std::dynamic_pointer_cast<CollisionEvent>(e);

		if (collision) {
			auto first = TypeVertex(typeid(*collision->first));
			auto second = TypeVertex(typeid(*collision->second));

			if (mDestroyGraph.containsEdge(first, second))
				collision->second->destroyed(true);
			if (mDestroyGraph.containsEdge(second, first))
				collision->first->destroyed(true);
		}
	}

	void Scene::onUpdateGame (double seconds) {
		// Remove outlived shapes
		mShapes->removeIf(
			[] (shared_ptr<Shape> const &s) -> bool { return s->destroyed (); }
		);
		auto shapesCopy = std::vector<shared_ptr<Shape>>(
				mShapes->begin(), mShapes->end()
		);

		// TODO Is there another more performing way of safely iterating
		//  through the list without making a copy of it?
		for (auto &s: shapesCopy) {
			s->velocity(s->velocity() + seconds * s->acceleration());
			s->position(s->position() + seconds * s->velocity());
		}
	}

	void Scene::draw (sf::RenderTarget &t, sf::RenderStates s) const {
		t.draw(*mShapesView, s);
	}
}
