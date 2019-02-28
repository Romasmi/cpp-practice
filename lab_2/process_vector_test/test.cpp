#include "../sort_vector/process_vector.h"
#include "pch.h"

std::vector<double> in;
std::vector<double> out;
TEST(ProcessVector, EmptyVector) {
  in = {};
  out = {};
  ProcessVector(in);
  ASSERT_EQ(out, in);
}

/*TEST(ProcessVector, OneElementVector) {
        in = {1};
        out = {1};
        ProcessVector(in);
        ASSERT_EQ(out, in);
}*/
