#include <crank/core.hpp>

std::string load_file_content(const std::string &fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cout << "FAILED TO FETCH " << fileName << " FILE CONTENTS" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string line{}, content{};
  while (std::getline(file, line)) {
    content += line + '\n';
  }

  return content;
}

namespace crank {



}
