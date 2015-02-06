#include "config.h"

int main(int argc, char *argv[])
{
  config_t *config = config_read("test.cnf");
  config_destroy(config);
}
