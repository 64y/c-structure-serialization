
target_bin=$1
structures_dir=$2

full_path_target_bin=$PWD/${target_bin}
target_bin_hash=`md5sum ${full_path_target_bin} | awk '{ print $1 }'`
target_bin_birth_time=`date +%F_%T -u -r ${full_path_target_bin}`
target_bin_library_dir="/tmp/c_structure_serialization_${target_bin_hash}_${target_bin_birth_time}"
target_bin_library_dir_src="${target_bin_library_dir}/src"
target_bin_library_dir_src_structures="${target_bin_library_dir_src}/"${structures_dir}

rm ${target_bin_library_dir_src} -rf
mkdir ${target_bin_library_dir_src} -p
cp /home/pavel/Workspace/c-structure-serialization/generate_codecs/res/* ${target_bin_library_dir} -r
if [ -d "include/${structures_dir}" ];
then
	cp include/${structures_dir}/* "${target_bin_library_dir_src}/${structures_dir}" -r
fi
if [ -d "src/${structures_dir}" ];
then
	cp src/${structures_dir} "${target_bin_library_dir_src}/${structures_dir}" -r
fi
if [ -d ${structures_dir} ];
then
	cp ${structures_dir} "${target_bin_library_dir_src}" -r
fi


/home/pavel/Workspace/c-structure-serialization/generate_codecs/bin/generate_codecs ${target_bin_library_dir_src} ${structures_dir}

echo "END"

