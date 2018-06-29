#include "stdafx.h"
#include "utilities.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include <vector>

#include "windows.h"

#include <iterator>
#include <cstdlib> 

#include <experimental\filesystem>


#include "CMDDEFS.h"
#include "FILENAMEDEFS.h"

namespace fs = std::experimental::filesystem;

using namespace std;

vector<mesh> meshes;

float pivot = 0.5;
fs::path exportedFolder = fs::path(fs::current_path().string() + "/" + exportedFolderRelative);

int main(int argc, char** argv)
{
	if (argv[1] != CMD_getAllFilesInFolder)
	{
		++argv;
		vector<string> filenames;
		for (int i=0; i<sizeof(argv-1); ++i)
		{
			filenames.push_back(*argv++);
		}
		
		meshes.resize(argc - 1);
		int temp_result = findVertices(filenames);
		findFaces(filenames);
		saveOBJToFile(filenames);
		switch (temp_result)
		{
		case 0: break;
		default: cout << "Error in mesh " << temp_result - 1 << endl << endl;
		}

		cout << "Done. " << argc - 1 << " meshes processed.\n";

		for (int i = 0; i < argc - 1; ++i)
		{
			cout << "--- MESH " << i + 1 << " DATA ---" << endl
				<< "Found " << meshes[i].number_of_vertices << " vertices" << endl
				<< "Found " << meshes[i].number_of_faces << " faces" << endl << endl;
			if (meshes[i].invalid_vertex_indices.size() > 0)
			{
				cout << "WARNING: there are " << meshes[i].invalid_vertex_indices.size() << " invalid vertices in this mesh!" << endl << endl;
			}
			/*for (int j = 0; j < meshes[i].vertices.size(); ++j)
			{
				cout << "Mesh " << i+1 << " vertex " << j+1 << " x: " << meshes[i].vertices[j].x<<endl;
				cout << "Mesh " << i+1 << " vertex " << j+1 << " y: " << meshes[i].vertices[j].y<<endl;
				cout << "Mesh " << i+1 << " vertex " << j+1 << " z: " << meshes[i].vertices[j].z<<endl<<endl;
			}*/
		}
	}
	else
	{
		fs::create_directory(fs::current_path().string() + "/" + exportedFolderRelative);
		

		vector<string> foundFiles(fileFinderByExtension(fs::current_path().string(), master_extension));

		meshes.resize(foundFiles.size());
		findVertices(foundFiles);
		cout << "Vertices - done." << endl;
		findFaces(foundFiles);
		cout << "Faces - done." << endl;
		findMaterials(foundFiles);
		cout << "Materials - done." << endl;
		meshCleaner(foundFiles);
		cout << "Cleaning - done." << endl;
		saveTexturesToFile(foundFiles);
		cout << "Saving - done." << endl;
			
		//fs::current_path().filename();
		
	}
	
    return 0;
}

