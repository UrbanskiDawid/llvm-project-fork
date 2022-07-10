// RUN: grep -Ev "// *[A-Z-]+:" %s \
// RUN:   | clang-format -style="{SpaceBeforeAndAfterOperator: SpaceBeforeAndAfter}" -lines=1:2 \
// RUN:   | FileCheck -strict-whitespace %s --check-prefixes=CHECKON
// CHECKON: {{^bool is = \(1 == 1\);}}
// CHECKON: {{^int a = 2 \+= 2;}}
bool is=(1==1);
int a=2+=2;
// RUN: grep -Ev "// *[A-Z-]+:" %s \
// RUN:   | clang-format -style="{SpaceBeforeAndAfterOperator: None}" -lines=3:4 \
// RUN:   | FileCheck -strict-whitespace %s --check-prefixes=CHECKOFF
// CHECKOFF: {{^bool is3 = 3==3}}
// CHECKOFF: {{^int a4 = 4\+=4;}}
bool is3=3==3;
int a4=4+=4;

