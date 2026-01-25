#include <iostream>
#include <memory>
using namespace std;

/**
 * @brief Represents an expensive resource on heap such as data from an Rtsp Source e.g. a camera stream.
 * This class needs to be used judiciously. Once its usage is done, it needs to be deleted. Can't keep it running in the
 * background.
 */
class RtspSource {
public:
  RtspSource() { cout << "RtspSource: Constrcutor called" << endl; }
  ~RtspSource() { cout << "RtspSource: Destrcutor called" << endl; }
};

class Camera {
public:
  Camera() { cout << "Camera: Constrcutor called" << endl; }
  ~Camera() { cout << "Camera: Destrcutor called" << endl; }

  /**
   * @brief Returns the shared pointer of the Rtsp Source. Creates a new one if it doesn't exists or else returns the
   * existing one. Uses weak ptr.
   */
  shared_ptr<RtspSource> getRtspSource() {
    shared_ptr<RtspSource> sharedPtr = m_weakRtspSource.lock();
    if (!sharedPtr) {
      sharedPtr = make_shared<RtspSource>();
      m_weakRtspSource = sharedPtr;
    }
    return sharedPtr;
  }
  weak_ptr<RtspSource> m_weakRtspSource;

  /**
   * @brief Returns the shared pointer of the Rtsp Source. Creates a new one if it doesn't exists or else returns the
   * existing one. Uses strong ptr.
   */
  shared_ptr<RtspSource> getRtspSource2() {
    if (!m_strongRtspSource)
      m_strongRtspSource = make_shared<RtspSource>();

    return m_strongRtspSource;
  }
  shared_ptr<RtspSource> m_strongRtspSource;
};

void demonstrateStrongPointer() {
  Camera *cmr = new Camera();
  cout << ".........." << endl;
  /**
   * @brief Create the RtspSource using Strong Pointer.
   * The problem here is, at this point the RtspSource object is created but not used anywhere, therefore the reference
   * count should drop to 0 & the RtspSource object should be deleted. But it does not happen because Camera is keeping
   * the m_rtspSource alive.
   */
  cmr->getRtspSource2();

  cout << ".........." << endl;
  delete cmr;
  /**
   * The shared pointer gets deleted at this point, when the Camera object gets deleted. In a complex program, a camera
   * object might be running for the entire lifespan of the application. We might not want the RtspSource to be running
   * that long.
   */
}

void demonstrateWeakPointer() {
  Camera *cmr = new Camera();
  cout << ".........." << endl;
  /**
   * @brief Creates RTSPSource using weak pointer
   * The problem with strong pointer is solved in this. The moment this call ends, the RTSPSource gets deleted
   * regardless of the camera object's lifespan.
   *
   */
  cmr->getRtspSource();
  cout << ".........." << endl;
  delete cmr;
}

// Uncomment one-at-a-time to see the behavior.
int main() {
  demonstrateStrongPointer();
  // demonstrateWeakPointer();
  return 0;
}