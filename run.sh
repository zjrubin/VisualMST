#!/bin/bash

echo "Generate vertices? (y/n):"
read answer

if [ "$answer" == "y" ] || [ "$answer" == "yes" ]
then
    echo $answer

    echo "How many verticies?"
    read vertices
    echo $vertices

    echo "Min coordinate value?"
    read min_coord_val

    echo "Max coordinate value?"
    read max_coord_val

    echo "Desired path to new vertex file?"
    read vertex_file_path
    folders=`dirname "$vertex_file_path"`
    filename=`basename "$vertex_file_path"`
    mkdir -p $folders # Recursively create folders
    
    python3 generate_vertices.py -n $vertices --min $min_coord_val --max $max_coord_val -o $vertex_file_path
    echo "Verticies generated..."

else # Vertex file already exists
    echo "Path to existing vertex file?"
    read vertex_file_path
fi

echo "Desired path to new MST outfile?"
read MST_outfile_path

echo "Creating MST..."
make > /dev/null # make sure mst program is built
./mst -m prims -i $vertex_file_path -o $MST_outfile_path
echo "Finished creating MST..."


echo "Graph MST? (y/n):"
read answer

if [ "$answer" == "y" ] || [ "$answer" == "yes" ]
then
    python3 graph.py -i $MST_outfile_path
fi

echo "Done"
echo "Exiting..."
