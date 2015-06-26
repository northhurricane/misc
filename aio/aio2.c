/*用于尝试将iocb和自定义数据关联*/
#include <libaio.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

void io_setup_error(int error_no)
{
  switch (error_no)
  {
  case -EAGAIN:
    printf("EAGAIN\n");
    break;
  case -EFAULT:
    printf("EFAULT\n");
    break;
  case -EINVAL:
    printf("EINVAL\n");
    break;
  case -ENOMEM:
    printf("ENOMEM\n");
    break;
  case -ENOSYS:
    printf("ENOSYS\n");
    break;
  default:
    printf("unknown\n");
  }
  printf("io_setup error.errno %d\n", error_no);
}

struct iocb_extra_struct
{
  struct iocb cb;
  void *extra;
};

typedef struct iocb_extra_struct iocb_extra_t;

int main(int argc, char *argv[])
{
  io_context_t ctx;
  struct io_event event;
  int io_event_cnt = 10;
  int fd, fd2;
  char *file = "hello.txt";
  char *file2 = "hello2.txt";
  char *content = "1234567890";
  char *content2 = "abcdefg";
  struct timespec timeout;
  iocb_extra_t io;
  iocb_extra_t io2;
  struct iocb *p[2];
  int ret;
  int total_write, finished;

  printf("hello aio.\n");

  memset(&ctx, 0x0, sizeof(ctx));
  if (0 != (ret = io_setup(io_event_cnt, &ctx)))
  {
    io_setup_error(ret);
    return -1;
  }

  if ((fd = open(file, O_CREAT|O_WRONLY, 0644)) < 0)
  {
    printf("open 1 error");
    io_destroy(ctx);
    return -1;
  }

  if ((fd2 = open(file2, O_CREAT|O_WRONLY, 0644)) < 0)
  {
    printf("open 2 error");
    io_destroy(ctx);
    return -1;
  }

  io_prep_pwrite((struct iocb*)&io, fd, content, strlen(content), 0);
  io.extra = file;
  io_prep_pwrite((struct iocb*)&io2, fd2, content2, strlen(content2), 0);
  io2.extra = file2;
  p[0] = (struct iocb*)&io;
  p[1] = (struct iocb*)&io2;
  total_write = 2;  //进行两个文件的写入
  finished = 0;

  if (2 != io_submit(ctx, 2, p))
  {
    io_destroy(ctx);
    printf("io_submit error\n");
    return -1;
  }
  printf("submitted\n");

  timeout.tv_sec = 0;
  timeout.tv_nsec = 500000000;
  while(1)
  {
    if (1 == io_getevents(ctx, 0, 1, &event, &timeout))
    {
      if (event.obj == (struct iocb*)&io)
      {
        printf("file 1 finished\n");
        printf("file 1 aio extra is %s\n"
               , ((iocb_extra_t*)(event.obj))->extra);
        close(fd);
      }
      if (event.obj == (struct iocb*)&io2)
      {
        printf("file 2 finished\n");
        printf("file 2 aio extra is %s\n"
               , ((iocb_extra_t*)(event.obj))->extra);
        close(fd2);
      }
      finished++;
      if (finished == total_write)
      {
        break;
      }
    }
  }
  printf("finish write.\n");

  io_destroy(ctx);

  return 0;
}
