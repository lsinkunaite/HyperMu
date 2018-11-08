#!/bin/bash

echo "==============================="
#echo "Enter z-shift: "
#echo -e "\n"
#read zshift
#echo "Enter phi-shift: "
#echo -e "\n"
#read phishift

#echo "Current presets: z-shift = $zshift, phi-shift = $phishift"

declare -a phiarr=("0" "25" "50" "75" "100")
declare -a zarr=("0" "15" "30" "45" "60")
declare -a btype=("mudecay" "goldcascade")

mbtype='param name='
mzshift='param zshift='
mphishift='param phishift='
mhisto='param histoFile='
mbeam='beam'

file='recover.g4bl'

for i in "${phiarr[@]}"
do for j in "${zarr[@]}"
	do for k in "${btype[@]}"
		do

			beamtype="param name=${k}"
			zshift="param zshift=${j}"
			phishift="param phishift=${i}"
			histofile="param histoFile=..\\/..\\/simdata\\/recover\\/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_${i}mm_phi_${j}mm_z_shifted_fixed_\$evts\$name.root"
			beammu="beam gaussian beamX=0 beamY=0 beamZ=0 meanP=\$P nEvents=\$evts particle=mu-"
			beamX="beam goldcascade beamX=0 beamY=0 beamZ=0 meanP=\$P nEvents=\$evts particle=gamma"

			cd ~/code/g4bl

			sed -i "s/^$mbtype.*/$beamtype/g" $file
			sed -i "s/^$mzshift.*/$zshift/g" $file
			sed -i "s/^$mphishift.*/$phishift/g" $file
			sed -i "s/^$mhisto.*/$histofile/g" $file

			if [ "$k" == "mudecay" ]; then
				sed -i "s/^$mbeam.*/$beammu/g" $file
			else
				sed -i "s/^$mbeam.*/$beamX/g" $file
			fi

			echo "z = ${j}, phi = ${i}, beam=${k}..."
			g4bl $file
			echo "...successfully generated!"
			echo $'\n'


		done
	done
done


