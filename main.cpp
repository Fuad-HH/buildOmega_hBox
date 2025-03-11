//
// Created by Fuad Hasan on 3/11/25.
//

#include <Omega_h_build.hpp>
#include <Omega_h_library.hpp>
#include <Omega_h_vtk.hpp>
#include <iostream>

void askFilenameAndWrite(Omega_h::Mesh &mesh);
void writeVTK(Omega_h::Mesh &mesh, std::string filename);
void writeGMSH(Omega_h::Mesh &mesh, std::string filename);

int main(int argc, char **argv) {
    //********************* Read Input ************************//
    if (argc != 7) {
        std::cout << "Usage: " << argv[0] << " <lx> <ly> <lz> <nx> <ny> <nz>\n";
        return -1;
    }
    int lx = atoi(argv[1]);
    int ly = atoi(argv[2]);
    int lz = atoi(argv[3]);
    int nx = atoi(argv[4]);
    int ny = atoi(argv[5]);
    int nz = atoi(argv[6]);


    //**************** Create Mesh ************************//
    Omega_h::Library library(&argc, &argv);
    auto mesh = Omega_h::build_box(library.world(), OMEGA_H_SIMPLEX, lx, ly, lz, nx, ny, nz, false);

    //**************** Print Mesh Properties ************************//
    int nverts = mesh.nverts();
    int nedges = mesh.nedges();
    int nfaces = mesh.nfaces();
    int ncells = mesh.nelems();
    int dim = mesh.dim();

    std::string message = "Mesh Properties: \n";
    message += "Number of Vertices: " + std::to_string(nverts) + "\n";
    message += "Number of Edges: " + std::to_string(nedges) + "\n";
    message += "Number of Faces: " + std::to_string(nfaces) + "\n";
    message += "Number of Cells: " + std::to_string(ncells) + "\n";
    message += "Dimension: " + std::to_string(dim) + "\n";

    std::cout << message;

    //***************** Write Mesh ****************************//
    printf("Do you want to write the mesh? (y/n): ");
    char c;
    std::cin >> c;
    if (c == 'y') {
        askFilenameAndWrite(mesh);
    }
    else if (c == 'n') {
        printf("Mesh not written.\n");
        printf("Want to write in VTK format instead? (y/n): ");
        std::cin >> c;
        if (c == 'y') {
            printf("\nEnter the file name with .vtk extension: ");
            std::string filename;
            std::cin >> filename;
            writeVTK(mesh, filename);
        }
    }
    else {
        printf("Invalid input\n");
        askFilenameAndWrite(mesh);
    }

    return 0;
}

void askFilenameAndWrite(Omega_h::Mesh &mesh) {
    printf("\nEnter the file name with .osh extension: ");
    std::string filename;
    std::cin >> filename;
    printf("\nWriting mesh to %s\n", filename.c_str());
    Omega_h::binary::write(filename, &mesh);

    printf("Want to write in VTK format too? (y/n): ");
    char c;
    std::cin >> c;
    if (c == 'y') {
        writeVTK(mesh, filename+".vtk");
    }
    else if (c == 'n') {
        printf("VTK not written.\n");
    }
    else {
        printf("Invalid input. but VTK will be written.\n");
        writeVTK(mesh, filename+".vtk");
    }

    printf("Want to write in GMSH format too? (y/n): ");
    std::cin >> c;
    if (c == 'y') {
        writeGMSH(mesh, filename+".msh");
    }
    else if (c == 'n') {
        printf("GMSH not written.\n");
    }
    else {
        printf("Invalid input. but GMSH will be written.\n");
        writeGMSH(mesh, filename+".msh");
    }
}

void writeVTK(Omega_h::Mesh &mesh, std::string filename) {
    printf("Writing vtk to %s\n", filename.c_str());
    Omega_h::vtk::write_parallel(filename, &mesh);
}

void writeGMSH(Omega_h::Mesh &mesh, std::string filename) {
    printf("Writing gmsh to %s\n", filename.c_str());
    Omega_h::gmsh::write(filename, &mesh);
}
