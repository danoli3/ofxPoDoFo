#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    clipboardContents = "<empty>";
    
       dir.listDir("PDF");
        dir.allowExt("pdf");
        dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

        //allocate the vector to have as many ofImages as files
        if( dir.size() ){
            images.assign(dir.size(), ofImage());
        }

        // you can now iterate through the files and load them into the ofImage vector
        for(int i = 0; i < (int)dir.size(); i++){
            pdfs[i].load(dir.getPath(i));
        }
        currentImage = 0;


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0, 0, 0, 0);

    ofSetColor(255);

//    ofDrawBitmapString("openFrameworks can programatically interact with the clipboard!", 10, 14);
//    ofDrawBitmapString("    Press 1 to send \"Hello World!\" to the clipboard.", 10, 28);
//    ofDrawBitmapString("    Press 2 to see the clipboard contents: " + clipboardContents, 10, 42);
    
    
    if (dir.size() > 0){
            ofSetColor(ofColor::white);
            //images[currentImage].draw(300,50);
        
            pdfs[currentImage].draw();

            ofSetColor(ofColor::gray);
            string pathInfo = dir.getName(currentImage) + " " + dir.getPath(currentImage) + "\n\n" +
                "press any key to advance current image\n\n" +
                "many thanks to hikaru furuhashi for the OFs";
            ofDrawBitmapString(pathInfo, 300, images[currentImage].getHeight() + 80);
        }

        ofSetColor(ofColor::gray);
        for(int i = 0; i < (int)dir.size(); i++){
            if(i == currentImage) {
                ofSetColor(ofColor::red);
            }    else {
                ofSetColor(ofColor::black);
            }
            string fileInfo = "file " + ofToString(i + 1) + " = " + dir.getName(i);
            
            ofDrawBitmapString(fileInfo, 50,i * 20 + 50);
        }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (dir.size() > 0){
        currentImage++;
        currentImage %= dir.size();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
