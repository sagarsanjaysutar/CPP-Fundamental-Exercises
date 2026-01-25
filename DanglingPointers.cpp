/**
 * @brief Demonstrates the use of Weak Pointers to avoid Dangling Pointer issues.
 * 
 * The term "Dangling Pointer" refers to a situation where a raw pointer continues to reference a memory location
 * after the object has been deleted by a smart pointer.
 */

#include <iostream>
#include <memory>

using namespace std;

class RtspSource {
public:
  RtspSource(int id) : m_id(id) { cout << "RtspSource: Constructor called" << endl; }
  ~RtspSource() { cout << "RtspSource: Destructor called" << endl; }

  int m_id;
};

void demonstrateDanglingPointer() {
  RtspSource *rtspSource;
  {
    shared_ptr<RtspSource> strongRtspSource = make_shared<RtspSource>(10);
    rtspSource = strongRtspSource.get();
    cout << "Inside Scope: " << rtspSource->m_id << endl;
  }

  /**
   * At this point, the shared pointer has gone out of scope & deleted the underlying RtspSource object but the
   * `rtspSource` pointer still holds the address.
   *
   * Note: We have added an arbitary process below because this is a dummy example & the `rtspSource` can still be used
   * to access the deleted object.
   */
  int *distraction = new int[100];
  for (int i = 0; i < 20000; i++)
    distraction[i] = 999;

  // Dangling pointer issue is seen here.
  cout << "Outside Scope: " << rtspSource->m_id << endl;
}

void demonstrateSafeUsage() {  
  weak_ptr<RtspSource> weakRtspSource;
  {
    // We created a shared pointer and assigned it to a weak pointer.
    shared_ptr<RtspSource> strongRtspSource = make_shared<RtspSource>(20);
    weakRtspSource = strongRtspSource;

    // Safe to use within this scope.
    if (shared_ptr<RtspSource> rtspSource = weakRtspSource.lock()) {
      cout << "Inside Scope: " << rtspSource->m_id << endl;
    }
  }

  // Outside the scope, we check if the object is still alive using weak pointer
  if (shared_ptr<RtspSource> rtspSource = weakRtspSource.lock()) {
    cout << "Outside Scope: " << rtspSource->m_id << endl;
  } else {
    cout << "Outside Scope: RtspSource object has been deleted." << endl;
  }
  
}

int main() {
  demonstrateSafeUsage();
  return 0;
}