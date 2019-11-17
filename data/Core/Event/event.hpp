#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

using namespace std;

class Event {
public:
    Event(string eventType, wxEvent * caller) {
        this->caller = caller;
        this->eventType = eventType;
    }
    string stringifyPath() {
        string label = "";
        vector<string>::reverse_iterator it;
        for(it = path.rbegin(); it != path.rend(); it++) {
            label.append((*it));
            if(it + 1 == path.rend()) {
                continue;
            }
            label.append(".");
        }
        return label;
    }
    wxEvent * caller;
    string eventType;
    vector<string> path;
};

#endif // EVENT_HPP_INCLUDED
