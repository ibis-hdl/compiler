#include <testsuite/syntax/dataset.hpp>
#include <testsuite/util/cli_args.hpp>

#include <testsuite/namespace_alias.hpp>

namespace testsuite::syntax {

dataset::dataset(std::string_view testcase_group)
    : testsuite::util::dataset_loader(testcase_group)
{
    set_builtin(std::make_unique<dataset::compile_builtin>());
}

}  // namespace testsuite::syntax
