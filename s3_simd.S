.text
.align 4
.global s3_add16x8
.type   s3_add16x8,@function
s3_add16x8:
  entry          a1,16              # prepare windowed registers and reserve 16 bytes of stack
  wsr.sar        a5                 # set the numbers of bits to bits to right-shift from a5
  ee.vld.128.ip  q1,a3,16           # load 8 "B" values into Q1 from A3, then add 16 to A3 - reusing this
  movi.n         a6, 0              # set a6 = 0
  movi.n         a7, 16             # set a7 = 16 ... this could/should be passed in as an argument via a#
  loop:
    beq            a6, a7, exit     # branch to "exit" if a6 == a7
    ee.vld.128.ip  q0,a2,16         # load 8 "A" values into Q0 from A2, then move the pointer by 16
    ee.vmul.s16    q2,q0,q1         # C = A*B then >> by wsr.sar
    ee.vst.128.ip  q2,a4,16         # store the 8 "C" values, then move the pointer by 16
    addi           a6, a6, 1        # increment a6
    j              loop             # jump to "loop"
  exit:
    movi.n        a2,0              # return value of 0 to function call
    retw.n                          # restore state (windowed registers) and return to caller
