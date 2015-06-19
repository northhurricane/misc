#include <libaio.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

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
  struct iocb io;
  struct iocb io2;
  struct iocb *p[2];
  int ret;

  printf("hello aio.\n");

  memset(&ctx, 0x0, sizeof(ctx));
  if (0 != (ret = io_setup(io_event_cnt, &ctx)))
  {
    switch (ret)
    {
    case -EAGAIN:
      printf("1\n");
      break;
    case -EFAULT:
      printf("2\n");
      break;
    case -EINVAL:
      printf("3\n");
      break;
    case -ENOMEM:
      printf("4\n");
      break;
    case -ENOSYS:
      printf("5\n");
      break;
    default:
      printf("6\n");
    }
    printf("io_setup error.errno %d\n", ret);
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

  io_prep_pwrite(&io, fd, content, strlen(content), 0);
  io_prep_pwrite(&io2, fd2, content2, strlen(content2), 0);
  p[0] = &io;
  p[1] = &io2;

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
      close(fd);
      break;
    }
    printf("havent’t done\n");
  }
  printf("finish write.\n");

  io_destroy(ctx);

  return 0;
}

