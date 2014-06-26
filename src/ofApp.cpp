#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    currentPosition = 0;
    numServers = 0;
    
    loadStreams(); //Load all the streams from XML
    
    if(ipcams.size()>0){
        currentHttpAddress = ipcams[0].getURL(); //
    }
    
    ipGrabber.setURI(currentHttpAddress);
    ipGrabber.connect();
    
    syphonServer.setName("ipCamReceiver");

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ipGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(255);
    ipGrabber.draw(0, 0, ofGetWidth(),ofGetHeight());
    
    syphonServer.publishScreen();
    
    ofDrawBitmapStringHighlight("Press 'u' to set the entire HTTP address.\nPress 'r' to reset the connection\nPress 's' to try the next stream\nCurrent App FPS: " + ofToString(ofGetFrameRate()) + "\nCurrent Feed FPS: " + ofToString(ipGrabber.getFrameRate()) + "\nCurrent address:" + currentHttpAddress, 20,20);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='s'){
        if(ipcams.size()>0){
        currentPosition++;
        currentPosition = currentPosition%numServers;
        currentHttpAddress = ipcams[currentPosition].getURL();
        ipGrabber.setURI(currentHttpAddress); //This will need to be modified if you need to access a feed that has a username/password
        ipGrabber.reset();
        ipGrabber.connect();
        }
    }
    
    if (key=='u') { //Set custom URL
        currentHttpAddress = ofSystemTextBoxDialog("Set Full Address String  - for example: http://192.168.0.3:8080/ipvideo");
        ipGrabber.setURI(currentHttpAddress);
        ipGrabber.reset();
        ipGrabber.connect();

    }
    
    if (key=='r') {
        ipGrabber.reset();
        ipGrabber.connect();
    }

}

void ofApp::loadStreams()
{
    
    // all of these cameras were found using this google query
    // http://www.google.com/search?q=inurl%3A%22axis-cgi%2Fmjpg%22
    // some of the cameras below may no longer be valid.
    
    // to define a camera with a username / password
    //ipcams.push_back(IPCameraDef("http://148.61.142.228/axis-cgi/mjpg/video.cgi", "username", "password"));
    
	ofLog(OF_LOG_NOTICE, "---------------Loading Streams---------------");
    
	ofxXmlSettings XML;
    
	if(XML.loadFile("streams.xml"))
    {
        
        XML.pushTag("streams");
        std::string tag = "stream";
		
		int nCams = XML.getNumTags(tag);
		
		for(std::size_t n = 0; n < nCams; n++)
        {
            
            IPCameraDef def(XML.getAttribute(tag, "name", "", n),
                            XML.getAttribute(tag, "url", "", n),
                            XML.getAttribute(tag, "username", "", n),
                            XML.getAttribute(tag, "password", "", n));
            
            
            std::string logMessage = "STREAM LOADED: " + def.getName() +
			" url: " +  def.getURL() +
			" username: " + def.getUsername() +
			" password: " + def.getPassword();
            
            ofLogNotice() << logMessage;
            
            ipcams.push_back(def);
            
		}
		
		XML.popTag();
        
	}
    else
    {
		ofLog(OF_LOG_ERROR, "Unable to load streams.xml.");
	}
    
	ofLog(OF_LOG_NOTICE, "-----------Loading Streams Complete----------");
    
    numServers = ipcams.size();
    
    cout<<ipcams.size();

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
