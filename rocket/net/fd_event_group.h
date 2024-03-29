#ifndef ROCKET_NET_FD_EVENT_GROUP_H__
#define ROCKET_NET_FD_EVENT_GROUP_H__
#include<vector>
#include"fd_event.h"
#include "../common/mutex.h"
namespace rocket{
class FdEventGroup {

 public:

  FdEventGroup(int size);

  ~FdEventGroup();
  FdEvent* getFdEvent(int fd);

 public:
  static FdEventGroup* GetFdEventGroup();

 private:
  int m_size {0};
  std::vector<FdEvent*> m_fd_group;
  Mutex m_mutex;

};

}

#endif