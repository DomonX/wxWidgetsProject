#ifndef EVENTDATA_H_INCLUDED
#define EVENTDATA_H_INCLUDED

class EventData {
public:
    map<string, EventData *> children;
    EventData() {

    }

};

#endif // EVENTDATA_H_INCLUDED
