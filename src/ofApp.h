#pragma once

#include "ofMain.h"
#include "IPVideoGrabber.h"
#include "ofxXmlSettings.h"
#include "ofxSyphon.h"

//This example combines bakercp's ipVideoGrabber example with syphon for an easy to use binary so that you can use an address from an IP cam in something like VDMX
//bakercp also has a great example of doing this exact same thing here - https://github.com/bakercp/IPCAM2SYPHON - but I just wanted to make this into a simple full screen implementation and release it as a binary for non-programmers to use

using ofx::Video::IPVideoGrabber;

class IPCameraDef
{
public:
    IPCameraDef()
    {
    }
    
    IPCameraDef(const std::string& url): _url(url)
    {
    }
    
    IPCameraDef(const std::string& name,
                const std::string& url,
                const std::string& username,
                const std::string& password):
    _name(name),
    _url(url),
    _username(username),
    _password(password)
    {
    }
    
    void setName(const std::string& name) { _name = name; }
    std::string getName() const { return _name; }
    
    void setURL(const std::string& url) { _url = url; }
    std::string getURL() const { return _url; }
    
    void setUsername(const std::string& username) { _username = username; }
    std::string getUsername() const { return _username; }
    
    void setPassword(const std::string& password) { _password = password; }
    std::string getPassword() const { return _password; }
    
    
private:
    std::string _name;
    std::string _url;
    std::string _username;
    std::string _password;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadStreams();
    
        IPVideoGrabber ipGrabber;
    
        string currentHttpAddress;
    
        ofxSyphonServer syphonServer;
        std::vector<IPCameraDef> ipcams;
    
    int numServers;
    int currentPosition;
};

