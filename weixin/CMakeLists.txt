aux_source_directory(. tool2_file) #查找当前目录下的tool1相关文件
add_library(tool2lib ${tool2_file})   #将他们编译为一个叫tool1lib的文件
target_link_libraries(tool2lib sqlite3)# 链接本地的sqlite3库