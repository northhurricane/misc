define process_show_mysqld
  shell ps -ef | grep mysqld | grep -v 'bash' | grep -v 'grep'
end

document process_show_mysqld
  show mysqld process info
  usage: process_show_mysqld
end