// RUN: grep -Ev "// *[A-Z-]+:" %s \
// RUN:   | clang-format -style="{SpaceBeforeAndAfterOperator: SpaceBeforeAndAfter}" \
// RUN:   | FileCheck -strict-whitespace %s
bool is=(1==1);
// CHECK: {{^bool is=\(1\ ==\ 1\);}}

