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
#ifndef NON_GRAVITAR_EVENT_LISTENER
#define NON_GRAVITAR_EVENT_LISTENER

#include <cstdint>
#include <set>

template<typename T> using set = std::set<T>;


namespace gvt {
	class EventListener;

    struct Event {
    	protected:
    		Event() = default;
    	public:
			virtual ~Event() = default;
    };

	class EventDispatcher {
		private:
			set<EventListener*> mListeners;
		public:
			~EventDispatcher();
			void attachListener(EventListener &l);
			void detachListener(EventListener &l);
			void notify(Event *e) const;
	};

	class EventListener {
		public:
			virtual void handle(Event *e) = 0;
	};
}


#endif
