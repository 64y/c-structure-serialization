#!/bin/bash

project_name=c_structure_serialization
project_home=~/.${project_name}

resources_dir="res"
target_dir="bin"
library_dir="lib"

install() {
	make build
	mkdir -p ${project_home}
	mkdir -p ${project_home}/include/${project_name}
	cp include/${project_name}/serializer.h ${project_home}/include/${project_name}/serializer.h
	mkdir -p ${project_home}/include/${project_name}/utils
	cp include/${project_name}/utils/data.h ${project_home}/include/${project_name}/utils/data.h
	cp ${target_dir}/* ${project_home}
	cp ${library_dir}/* ${project_home}
	cp ${resources_dir}/* ${project_home}/${resources_dir} -r
	make clean

	echo "export C_STRUCTURE_SERIALIZATION_HOME=${project_home}" >> ~/.bashrc
	source ~/.bashrc
}

uninstall() {
	rm -rf ${project_home}
	unset C_STRUCTURE_SERIALIZATION_HOME
	sed -i "/export C_STRUCTURE_SERIALIZATION_HOME/d" ~/.bashrc
}
