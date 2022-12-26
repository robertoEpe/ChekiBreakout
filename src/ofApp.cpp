#include "ofApp.h"

// Is a small game EVERYTHING will be here
namespace {

	int window_width = 980;
	int window_height = 640;

	class GameObject {
	public:
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

	class Ball : public GameObject {
	public:

		Ball() : m_pos{ window_width/2, window_height/2 }, m_radius{ 10 }, m_vel{ 5, 7 } {

		}


		void Draw() override {
			ofSetColor(ofColor::white);
			ofDrawCircle(m_pos, m_radius);
		}

		void Update() override {
			if ((GetPos().x - GetRadius()) <= 0) {
				FlipDirectionX();
			}
			else if ((GetPos().x + GetRadius()) >= ofGetWidth()) {
				FlipDirectionX();
			}

			if ((GetPos().y - GetRadius()) <= 0) {
				FlipDirectionY();
				
			}
			else if ((GetPos().y + GetRadius()) >= ofGetHeight()) {
				FlipDirectionY();
				ResetBall();
			}

			m_pos += m_vel;
		}


		const glm::vec2& GetPos() const {
			return m_pos;
		}

		const float& Radius() const {
			return m_radius;
		}

		const glm::vec2& GetPos()  {
			return m_pos;
		}

		const float& GetRadius() {
			return m_radius;
		}

		void FlipDirectionX() {
			m_vel.x *= -1;
		}

		void FlipDirectionY() {
			m_vel.y *= -1;
		}

		void ResetBall() {
			m_pos = { ofGetWidth() / 2.f, ofGetHeight() / 2.f };
		}

		bool CollideRectangle(ofRectangle rect) {

			if ((m_pos.y + m_radius) > rect.getTop()
				&& (m_pos.y - m_radius) < rect.getBottom()
				&& rect.getLeft() < (m_pos.x + m_radius)
				&& rect.getRight() > (m_pos.x - m_radius))
			{
				return true;
			}

			return false;
			
		}



		void SetVelocityX(float x_vel) {
			m_vel = { x_vel, m_vel.y};
		}
		
	private:
		glm::vec2 m_pos;
		float m_radius;
		glm::vec2 m_vel;
	};

	class Paddle : public GameObject {
	public:
		Paddle() : m_pos{window_width/2, window_height - 60} {}

		void ChangePos(float new_posX) {
			new_posX -= m_width / 2;
			m_pos.x = new_posX;
		}

		ofRectangle GetRectangle() const {
			return {m_pos, m_width, m_thikness };
		}

		ofRectangle GetRectangle() {
			return { m_pos, m_width, m_thikness };
		}


		virtual void Draw() override
		{
			ofSetColor(ofColor::blue);
			ofDrawRectangle(m_pos, m_width, m_thikness);
		}

		virtual void Update() override {

		}

	private:
		const float m_width = 100.f;
		const float m_thikness = 10.f;
		glm::vec2 m_pos;

	};

	Paddle paddle{};
	Ball ball{};
}

//--------------------------------------------------------------
void ofApp::setup(){
	// The window title
	ofSetWindowTitle("Cheki Breakout");

	// Position of the window
	ofSetWindowPosition(100, 50);
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofSetCircleResolution(100);
	ofSetFrameRate(30);

	// Background color
	ofBackground(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update(){

	if (auto rect = paddle.GetRectangle() ; ball.CollideRectangle(rect)) {
		ball.SetVelocityX((ball.GetPos().x - (rect.getLeft() + rect.width / 2)) * 0.35f);
		ball.FlipDirectionY();
	}

	ball.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	paddle.Draw();
	ball.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	paddle.ChangePos(x);

}

////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){ 
//
//}
