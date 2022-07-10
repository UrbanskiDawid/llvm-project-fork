// RUN: grep -Ev "// *[A-Z-]+:" %s \
// RUN:   | clang-format -style="{SpaceBeforeAndAfterOperator:SpaceBeforeAndAfter}" -lines=1:2 \
// RUN:   | FileCheck -strict-whitespace %s
bool is=(1==1);
int a = 1+=1;
// CHECK: {{^bool is=\(1\ ==\ 1\);}}
// CHECK: {{^int a=1 + 1;}}
// RUN:   | clang-format -style="{SpaceBeforeAndAfterOperator:None}" -lines=3:4 \
// RUN:   | FileCheck -strict-whitespace %s
bool is2=(1==1);
int a2 = 1+=1;
// CHECK: {{^bool is2=\(1==1\);}}
// CHECK: {{^int a2=1+1;}}

