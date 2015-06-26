/*测试同一文件进行aio操作，偏移互相覆盖*/
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

int main(int argc, char *argv[])
{
  io_context_t ctx;
  struct io_event event;
  int io_event_cnt = 10;
  int fd;
  char *file = "hello.txt";
  char *content = "1234567890";
  char *content2 = "abcdefg";
  struct timespec timeout;
  struct iocb io;
  struct iocb io2;
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

  io_prep_pwrite(&io, fd, content, strlen(content), 0);
  io_prep_pwrite(&io2, fd, content2, strlen(content2), 6);
  p[0] = &io;
  p[1] = &io2;
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
      if (event.obj == &io)
      {
        printf("io 1 finished\n");
      }
      if (event.obj == &io2)
      {
        printf("io 2 finished\n");
      }
      finished++;
      if (finished == total_write)
      {
        break;
      }
    }
  }
  printf("finish write.\n");

  close(fd);
  io_destroy(ctx);

  return 0;
}

