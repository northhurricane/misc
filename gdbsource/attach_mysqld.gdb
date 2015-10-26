define attach_mysqld
  shell echo attach $(ps -ef | grep mysqld | grep -v 'bash' | grep -v 'grep' | awk '{print $8 " " $2}' | grep mysqld | awk '{print $2}') > /tmp/attach_mysqld_impl.gdb
  source /tmp/attach_mysqld_impl.gdb
#  print $mysqld_prcs_id
#  echo "mysqld process id is " mysqld_prcs_id
#  attach $mysqld_prcs_id
end

document attach_mysqld
  attach gdb to mysqld process
  usage: attach_mysqld
end
