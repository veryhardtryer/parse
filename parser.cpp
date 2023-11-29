#include <iostream>
#include <sstream>
#include <ostream>
#include <string>

std::string removeAfter(const std::string& packet, int index, char marker) {
  size_t start = 0;
  size_t end = packet.size();
  while(index) {
    start = packet.find_first_of(marker, start) + 1;
    if(start == std::string::npos || start == 0) {
      return {};
    }
    --index;
  }
  end = packet.find_first_of(marker, start) + 1;

  if(end == std::string::npos || end == 0) {
    return {};
  }

  return packet.substr(start, end - start);
}

std::string selectBetween(const std::string& packet, int index,
    char open, char close) {
  size_t start = 0;
  size_t end = packet.size();

  while(index) {
    start = packet.find_first_of(open, start) + 1;
    if(start == std::string::npos || start == 0) {
      return {};
    }
    index--;
  }

  start = packet.find_first_of(open, start);
  end = packet.find_first_of(close, start) + 1;

  if(end == std::string::npos || end == 0 ||
     start == std::string::npos) {
    return {};
  }

  return packet.substr(start, end - start);
}

int main() {
  std::string input = "{[[1, 2], [3,4]]}{[1, 2, 3, 4]}{0};"\
                      "{[[5, 6], [7,8]]}{[4, 5, 6, 7]}{1};"\
                      "{[[9, 10], [11,12]]}{[8, 9, 10, 11]}{2};";

  for(size_t i = 0; i < 3; ++i) {
    std::string arg_packet = removeAfter(input, i, ';');
    std::cout << "PACKET" << i << ' ' << arg_packet << std::endl;
    for(size_t j = 0; j < 3; ++j) {
      std::string arg = selectBetween(arg_packet, j, '{', '}');
      std::cout << "ARG" << j <<  ' ' << arg << std::endl;
      if(j == 0) {
        std::string sequance = arg.substr(2, arg.size() - 4);
        std::cout << "SEQUANCE "  << sequance << std::endl;
        for(size_t k = 0; k < 2; ++k) {
          std::string chain = selectBetween(sequance, k, '[', ']');
          std::cout << "CHAIN" << k << ' ' << chain << std::endl;
        }
      }
    }
  }
  return 0;
}