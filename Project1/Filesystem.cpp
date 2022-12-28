#include "Filesystem.hpp"

int split(std::string text, char sep, std::string arr[], int size)
{
    int counter = 0;
    std::string temp = "";
    int textlenght = text.length();
    if (textlenght == 0) {
        //edge case
        return 0;
    }
    for (int i = 0; i < textlenght; i++) {
        if (text[i] == sep) {
            // condition to let me still assign the last section
            if (counter < (size - 1)) {
                // resets temp based on whether it see identifier
                arr[counter] = temp;
                counter++;
                temp = "";
            }
            else {
                // if it goes outof bounds it still assigns the temp to the last slot
                arr[counter] = temp;
                return -1;
            }
        }
        else {
            // adds the characters to temp
            temp += text[i];
        }
    }
    //makes sure last section gets assigned
    arr[counter] = temp;
    return counter + 1;
}

void writeCircs(std::string filename, std::vector<Circ> vec)
{
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < vec.size(); i++) {
        file << "Circ,";
        file << vec[i].name << ',';
        file << vec[i].color[0] << ',' << vec[i].color[1] << ',' << vec[i].color[2] << ',' << vec[i].color[3] << ',';
        file << vec[i].rad << ',';
        file << vec[i].position[0] << ',' << vec[i].position[1] << ',';
        file << vec[i].velocity[0] << ',' << vec[i].velocity[1] << ',';
        file << vec[i].acceleration[0] << ',' << vec[i].acceleration[1] << ',';
        file << vec[i].dynamic_physics << std::endl;

    }
    file.close();
}

void readinCircs(std::string filename, std::vector<Circ>& vec)
{
    vec.clear();
    std::ifstream file;
    file.open(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line != "") {
            if (line[0] == 'C') {
                std::string splitline[14];
                split(line, ',', splitline, 14);
                std::string name = splitline[1];
                int color[3];
                float pos[2], v[2], a[2];
                bool phys;
                color[0] = std::stoi(splitline[2]);
                color[1] = std::stoi(splitline[3]);
                color[2] = std::stoi(splitline[4]);
                int rad = std::stoi(splitline[6]);
                pos[0] = std::stof(splitline[7]);
                pos[1] = std::stof(splitline[8]);
                v[0] = std::stof(splitline[9]);
                v[1] = std::stof(splitline[10]);
                a[0] = std::stof(splitline[11]);
                a[1] = std::stof(splitline[12]);
                phys = std::stoi(splitline[13]);
                std::cout << name << ',' << pos[0] << ',' << pos[1] << std::endl;
                Circ tempcirc(name, color, rad, pos, v, a, phys);
                vec.push_back(tempcirc);
            }
        }
    }
}
