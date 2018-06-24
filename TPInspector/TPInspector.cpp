#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include "utilities.h"
#include <sstream>

#include <vector>

#include "windows.h"

#include <iterator>
#include <cstdlib> 

using namespace std;

vector<mesh> meshes;

float pivot = 0.5;

int main(int argc, char** argv)
{
	meshes.resize(argc-1);
	int temp_result = findVertices(argc-1, ++argv);
	findFaces(argc - 1, argv);
	saveOBJToFile(argc - 1, argv);
	switch (temp_result)
	{
	case 0: break;
	default: cout << "Error in mesh " << temp_result - 1 << endl << endl;
	}

	cout << "Done. " << argc-1 << " meshes processed.\n";

	for (int i = 0; i < argc - 1; ++i)
	{
		cout << "--- MESH " << i + 1 << " DATA ---" << endl
			<< "Found " << meshes[i].number_of_vertices << " vertices" << endl 
			<<"Found " << meshes[i].number_of_faces << " faces" << endl <<endl;
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

	
	
    return 0;
}

