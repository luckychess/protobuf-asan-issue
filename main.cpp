#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include <endpoint.pb.h>

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream in(argv[i]);
    in.seekg(0, in.end);
    size_t length = in.tellg();
    in.seekg(0, in.beg);
    std::cout << "Reading " << length << " bytes from " << argv[i] << std::endl;
    // Allocate exactly length bytes so that we reliably catch buffer overflows.
    std::vector<char> bytes(length);
    in.read(bytes.data(), bytes.size());
    assert(in);

    auto data = reinterpret_cast<const uint8_t *>(bytes.data());
    auto size = bytes.size();

    iroha::protocol::TxStatusRequest tx;
    tx.Clear();

    if (tx.ParsePartialFromString({data, data + size})) {
      std::cout << "Execution successful" << std::endl;
    } else {
      std::cout << "Execution failed" << std::endl;
    }
  }
}
