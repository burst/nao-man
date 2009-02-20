
#ifndef TOOLConnect_H
#define TOOLConnect_H

#include "Common.h"

class TOOLConnect; // forward reference

#  include <boost/shared_ptr.hpp>
#  include "synchro.h"
#  include "Sensors.h"
#  include "Vision.h"

#include "CommDef.h"
#include "DataSerializer.h"

//
// DataRequest struct definition
//

#define SIZEOF_REQUEST 10

struct DataRequest {
    bool info;
    bool joints;
    bool sensors;
    bool image;
    bool thresh;
    bool jpeg;
    bool objects;
    bool motion;
    bool local;
    bool comm;
};

static void
setRequest (DataRequest &r, byte buf[SIZEOF_REQUEST])
{
    r.info    = buf[0];
    r.joints  = buf[1];
    r.sensors = buf[2];
    r.image   = buf[3];
    r.thresh  = buf[4];
    r.jpeg    = buf[5];
    r.objects = buf[6];
    r.motion  = buf[7];
    r.local   = buf[8];
    r.comm    = buf[9];
}

//
// TOOLConnect class definition
//

class TOOLConnect
    : public Thread
{
public:
    TOOLConnect(boost::shared_ptr<Synchro> _synchro,
                boost::shared_ptr<Sensors> s,
                boost::shared_ptr<Vision> v);
    ~TOOLConnect();

    void run();

    std::string getRobotName();
    int getState() { return state; }

private:
    void reset();
    void receive       ()               throw(socket_error&);
    void handle_request(DataRequest& r) throw(socket_error&);
    void handle_command(int cmd)        throw(socket_error&);

    int state;
    // Serialized connection to remote host
    DataSerializer serial;

    // References to global data structures
    //   on the Aibo's, we have neither threads nor Sensors class
    boost::shared_ptr<Sensors> sensors; // thread-safe access to sensors
    boost::shared_ptr<Vision> vision; // access to vision processing
};

#endif /* TOOLConnect_H */
