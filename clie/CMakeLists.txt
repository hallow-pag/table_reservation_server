aux_source_directory(. tool1_file) #查找当前目录下的tool1相关文件
 
add_library(tool1lib ${tool1_file})   #将他们编译为一个叫tool1lib的文件
target_link_libraries(tool1lib jsoncpp)# 链接本地的sqlite3库/lib/libjson_linux-gcc-5.4.0_libmt.so