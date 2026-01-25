/**
 * @brief Demonstrates the use of Weak Pointer to resolve Circular Dependency between Parent and Child classes.
 *
 * The term "Circular Dependency" refers to a situation where two or more classes hold strong references to each other,
 * preventing their proper destruction and leading to memory leaks. This example illustrates how using weak pointers
 * can help break this cycle and ensure that resources are released appropriately.
 */
#include <iostream>
#include <memory>
using namespace std;

// Forward declaration so that parent could be added to the child.
class Camera;

class RtspSource {
public:
  // RTSPSource(Child) holds a strong reference to the parent.
  shared_ptr<Camera> m_strongParentPtr;

  // RTSPSource(Child) holds a weak reference to the parent.
  weak_ptr<Camera> m_weakParentPtr;

  RtspSource() { cout << "RtspSource: Constructor called" << endl; }
  ~RtspSource() { cout << "RtspSource: Destructor called" << endl; }
};

class Camera {
public:
  // Parent Camera owns RtspSource
  shared_ptr<RtspSource> m_strongRtspSource;

  Camera() { cout << "Camera: Constructor called" << endl; }
  ~Camera() { cout << "Camera: Destructor called" << endl; }
};

void demonstrateStrongPointer() {
  shared_ptr<Camera> cmr = make_shared<Camera>();

  // Initialise the RTSPSource in camera.
  cmr->m_strongRtspSource = make_shared<RtspSource>();

  // Initialise the parent in RTSPSource.
  cmr->m_strongRtspSource->m_strongParentPtr = cmr;

  /**
   * Once the scope of this function ends, the shared pointer for the camera should drop the reference as no one is
   * using camera. But it is unable to do so because RTSPSource holds it.
   *
   * What ends up happening is neither RTSPSource gets deleted neither the Camera resulting in Circular dependency.
   */
}

void demonstrateWeakPointer() {
  shared_ptr<Camera> cmr = make_shared<Camera>();

  // Initialise the RTSPSource in camera.
  cmr->m_strongRtspSource = make_shared<RtspSource>();

  // Create a tmp variable for the weak pointer to check if the parent exists. If not, initialise it.
  shared_ptr<Camera> prntPtrInChild = cmr->m_strongRtspSource->m_weakParentPtr.lock();
  if (!prntPtrInChild) {
    prntPtrInChild = cmr;
    cmr->m_strongRtspSource->m_weakParentPtr = prntPtrInChild;
  }

  /**
   * Once the scope of this function ends, the destructors are properly called.
   * 1. First the `prntPtrInChild` gets out of scope and reference count of Camera drops by 1.
   * 2. Then the `cmr` gets out of scope and reference count of Camera drops to 0. Therefore Camera is deleted.
   * 3. While deleting Camera, its member `m_strongRtspSource`'s reference count drops to 0 and therefore RtspSource is
   * deleted.
   * 4. While deleting RtspSource, its weak pointer to Camera does not affect anything as weak pointers do not
   * contribute to reference count.
   * 5. Thus, both Camera and RtspSource are properly deleted without any memory leaks.
   *
   */
}

// Uncomment one-at-a-time to see the behavior.
int main() {
  demonstrateStrongPointer();
  // demonstrateWeakPointer();
  return 0;
}
