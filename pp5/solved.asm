	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  main:
	# BeginFunc 600
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 600	# decrement sp to make space for locals/temps
	# _tmp0 = 5
	  li $t2, 5		# load constant value 5 into $t2
	  sw $t2, -20($fp)	# spill _tmp0 from $t2 to $fp-20
	# _tmp1 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -24($fp)	# spill _tmp1 from $t2 to $fp-24
	# _tmp2 = _tmp0 < _tmp1
	  lw $t0, -20($fp)	# fill _tmp0 to $t0 from $fp-20
	  lw $t1, -24($fp)	# fill _tmp1 to $t1 from $fp-24
	  slt $t2, $t0, $t1	
	  sw $t2, -28($fp)	# spill _tmp2 from $t2 to $fp-28
	# IfZ _tmp2 Goto _L0
	  lw $t0, -28($fp)	# fill _tmp2 to $t0 from $fp-28
	  beqz $t0, _L0	# branch if _tmp2 is zero 
	# _tmp3 = "Decaf runtime error: Array size is <= 0\n"
	  .data			# create string constant marked with label
	  _string1: .asciiz "Decaf runtime error: Array size is <= 0\n"
	  .text
	  la $t2, _string1	# load label
	  sw $t2, -32($fp)	# spill _tmp3 from $t2 to $fp-32
	# PushParam _tmp3
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -32($fp)	# fill _tmp3 to $t0 from $fp-32
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L0:
	# _tmp4 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -36($fp)	# spill _tmp4 from $t2 to $fp-36
	# _tmp5 = _tmp4 + _tmp0
	  lw $t0, -36($fp)	# fill _tmp4 to $t0 from $fp-36
	  lw $t1, -20($fp)	# fill _tmp0 to $t1 from $fp-20
	  add $t2, $t0, $t1	
	  sw $t2, -40($fp)	# spill _tmp5 from $t2 to $fp-40
	# _tmp6 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -44($fp)	# spill _tmp6 from $t2 to $fp-44
	# _tmp7 = _tmp5 * _tmp6
	  lw $t0, -40($fp)	# fill _tmp5 to $t0 from $fp-40
	  lw $t1, -44($fp)	# fill _tmp6 to $t1 from $fp-44
	  mul $t2, $t0, $t1	
	  sw $t2, -48($fp)	# spill _tmp7 from $t2 to $fp-48
	# PushParam _tmp7
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -48($fp)	# fill _tmp7 to $t0 from $fp-48
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp8 = LCall _Alloc
	  jal _Alloc         	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -52($fp)	# spill _tmp8 from $t2 to $fp-52
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# *(_tmp8) = _tmp0
	  lw $t0, -20($fp)	# fill _tmp0 to $t0 from $fp-20
	  lw $t2, -52($fp)	# fill _tmp8 to $t2 from $fp-52
	  sw $t0, 0($t2) 	# store with offset
	# _tmp9 = _tmp8 + _tmp6
	  lw $t0, -52($fp)	# fill _tmp8 to $t0 from $fp-52
	  lw $t1, -44($fp)	# fill _tmp6 to $t1 from $fp-44
	  add $t2, $t0, $t1	
	  sw $t2, -56($fp)	# spill _tmp9 from $t2 to $fp-56
	# x = _tmp9
	  lw $t2, -56($fp)	# fill _tmp9 to $t2 from $fp-56
	  sw $t2, -8($fp)	# spill x from $t2 to $fp-8
	# _tmp10 = 5
	  li $t2, 5		# load constant value 5 into $t2
	  sw $t2, -60($fp)	# spill _tmp10 from $t2 to $fp-60
	# _tmp11 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -64($fp)	# spill _tmp11 from $t2 to $fp-64
	# _tmp12 = _tmp10 < _tmp11
	  lw $t0, -60($fp)	# fill _tmp10 to $t0 from $fp-60
	  lw $t1, -64($fp)	# fill _tmp11 to $t1 from $fp-64
	  slt $t2, $t0, $t1	
	  sw $t2, -68($fp)	# spill _tmp12 from $t2 to $fp-68
	# IfZ _tmp12 Goto _L1
	  lw $t0, -68($fp)	# fill _tmp12 to $t0 from $fp-68
	  beqz $t0, _L1	# branch if _tmp12 is zero 
	# _tmp13 = "Decaf runtime error: Array size is <= 0\n"
	  .data			# create string constant marked with label
	  _string2: .asciiz "Decaf runtime error: Array size is <= 0\n"
	  .text
	  la $t2, _string2	# load label
	  sw $t2, -72($fp)	# spill _tmp13 from $t2 to $fp-72
	# PushParam _tmp13
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -72($fp)	# fill _tmp13 to $t0 from $fp-72
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L1:
	# _tmp14 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -76($fp)	# spill _tmp14 from $t2 to $fp-76
	# _tmp15 = _tmp14 + _tmp10
	  lw $t0, -76($fp)	# fill _tmp14 to $t0 from $fp-76
	  lw $t1, -60($fp)	# fill _tmp10 to $t1 from $fp-60
	  add $t2, $t0, $t1	
	  sw $t2, -80($fp)	# spill _tmp15 from $t2 to $fp-80
	# _tmp16 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -84($fp)	# spill _tmp16 from $t2 to $fp-84
	# _tmp17 = _tmp15 * _tmp16
	  lw $t0, -80($fp)	# fill _tmp15 to $t0 from $fp-80
	  lw $t1, -84($fp)	# fill _tmp16 to $t1 from $fp-84
	  mul $t2, $t0, $t1	
	  sw $t2, -88($fp)	# spill _tmp17 from $t2 to $fp-88
	# PushParam _tmp17
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -88($fp)	# fill _tmp17 to $t0 from $fp-88
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp18 = LCall _Alloc
	  jal _Alloc         	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -92($fp)	# spill _tmp18 from $t2 to $fp-92
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# *(_tmp18) = _tmp10
	  lw $t0, -60($fp)	# fill _tmp10 to $t0 from $fp-60
	  lw $t2, -92($fp)	# fill _tmp18 to $t2 from $fp-92
	  sw $t0, 0($t2) 	# store with offset
	# _tmp19 = _tmp18 + _tmp16
	  lw $t0, -92($fp)	# fill _tmp18 to $t0 from $fp-92
	  lw $t1, -84($fp)	# fill _tmp16 to $t1 from $fp-84
	  add $t2, $t0, $t1	
	  sw $t2, -96($fp)	# spill _tmp19 from $t2 to $fp-96
	# y = _tmp19
	  lw $t2, -96($fp)	# fill _tmp19 to $t2 from $fp-96
	  sw $t2, -12($fp)	# spill y from $t2 to $fp-12
	# _tmp20 = 3
	  li $t2, 3		# load constant value 3 into $t2
	  sw $t2, -100($fp)	# spill _tmp20 from $t2 to $fp-100
	# _tmp21 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -104($fp)	# spill _tmp21 from $t2 to $fp-104
	# _tmp22 = _tmp20 < _tmp21
	  lw $t0, -100($fp)	# fill _tmp20 to $t0 from $fp-100
	  lw $t1, -104($fp)	# fill _tmp21 to $t1 from $fp-104
	  slt $t2, $t0, $t1	
	  sw $t2, -108($fp)	# spill _tmp22 from $t2 to $fp-108
	# _tmp23 = *(x + -4)
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -112($fp)	# spill _tmp23 from $t2 to $fp-112
	# _tmp24 = _tmp20 < _tmp23
	  lw $t0, -100($fp)	# fill _tmp20 to $t0 from $fp-100
	  lw $t1, -112($fp)	# fill _tmp23 to $t1 from $fp-112
	  slt $t2, $t0, $t1	
	  sw $t2, -116($fp)	# spill _tmp24 from $t2 to $fp-116
	# _tmp25 = _tmp24 == _tmp21
	  lw $t0, -116($fp)	# fill _tmp24 to $t0 from $fp-116
	  lw $t1, -104($fp)	# fill _tmp21 to $t1 from $fp-104
	  seq $t2, $t0, $t1	
	  sw $t2, -120($fp)	# spill _tmp25 from $t2 to $fp-120
	# _tmp26 = _tmp22 || _tmp25
	  lw $t0, -108($fp)	# fill _tmp22 to $t0 from $fp-108
	  lw $t1, -120($fp)	# fill _tmp25 to $t1 from $fp-120
	  or $t2, $t0, $t1	
	  sw $t2, -124($fp)	# spill _tmp26 from $t2 to $fp-124
	# IfZ _tmp26 Goto _L2
	  lw $t0, -124($fp)	# fill _tmp26 to $t0 from $fp-124
	  beqz $t0, _L2	# branch if _tmp26 is zero 
	# _tmp27 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string3: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string3	# load label
	  sw $t2, -128($fp)	# spill _tmp27 from $t2 to $fp-128
	# PushParam _tmp27
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -128($fp)	# fill _tmp27 to $t0 from $fp-128
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L2:
	# _tmp28 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -132($fp)	# spill _tmp28 from $t2 to $fp-132
	# _tmp29 = _tmp28 * _tmp20
	  lw $t0, -132($fp)	# fill _tmp28 to $t0 from $fp-132
	  lw $t1, -100($fp)	# fill _tmp20 to $t1 from $fp-100
	  mul $t2, $t0, $t1	
	  sw $t2, -136($fp)	# spill _tmp29 from $t2 to $fp-136
	# _tmp30 = x + _tmp29
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t1, -136($fp)	# fill _tmp29 to $t1 from $fp-136
	  add $t2, $t0, $t1	
	  sw $t2, -140($fp)	# spill _tmp30 from $t2 to $fp-140
	# _tmp31 = 5
	  li $t2, 5		# load constant value 5 into $t2
	  sw $t2, -144($fp)	# spill _tmp31 from $t2 to $fp-144
	# *(_tmp30) = _tmp31
	  lw $t0, -144($fp)	# fill _tmp31 to $t0 from $fp-144
	  lw $t2, -140($fp)	# fill _tmp30 to $t2 from $fp-140
	  sw $t0, 0($t2) 	# store with offset
	# _tmp32 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -148($fp)	# spill _tmp32 from $t2 to $fp-148
	# _tmp33 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -152($fp)	# spill _tmp33 from $t2 to $fp-152
	# _tmp34 = _tmp32 < _tmp33
	  lw $t0, -148($fp)	# fill _tmp32 to $t0 from $fp-148
	  lw $t1, -152($fp)	# fill _tmp33 to $t1 from $fp-152
	  slt $t2, $t0, $t1	
	  sw $t2, -156($fp)	# spill _tmp34 from $t2 to $fp-156
	# _tmp35 = *(y + -4)
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -160($fp)	# spill _tmp35 from $t2 to $fp-160
	# _tmp36 = _tmp32 < _tmp35
	  lw $t0, -148($fp)	# fill _tmp32 to $t0 from $fp-148
	  lw $t1, -160($fp)	# fill _tmp35 to $t1 from $fp-160
	  slt $t2, $t0, $t1	
	  sw $t2, -164($fp)	# spill _tmp36 from $t2 to $fp-164
	# _tmp37 = _tmp36 == _tmp33
	  lw $t0, -164($fp)	# fill _tmp36 to $t0 from $fp-164
	  lw $t1, -152($fp)	# fill _tmp33 to $t1 from $fp-152
	  seq $t2, $t0, $t1	
	  sw $t2, -168($fp)	# spill _tmp37 from $t2 to $fp-168
	# _tmp38 = _tmp34 || _tmp37
	  lw $t0, -156($fp)	# fill _tmp34 to $t0 from $fp-156
	  lw $t1, -168($fp)	# fill _tmp37 to $t1 from $fp-168
	  or $t2, $t0, $t1	
	  sw $t2, -172($fp)	# spill _tmp38 from $t2 to $fp-172
	# IfZ _tmp38 Goto _L3
	  lw $t0, -172($fp)	# fill _tmp38 to $t0 from $fp-172
	  beqz $t0, _L3	# branch if _tmp38 is zero 
	# _tmp39 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string4: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string4	# load label
	  sw $t2, -176($fp)	# spill _tmp39 from $t2 to $fp-176
	# PushParam _tmp39
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -176($fp)	# fill _tmp39 to $t0 from $fp-176
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L3:
	# _tmp40 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -180($fp)	# spill _tmp40 from $t2 to $fp-180
	# _tmp41 = _tmp40 * _tmp32
	  lw $t0, -180($fp)	# fill _tmp40 to $t0 from $fp-180
	  lw $t1, -148($fp)	# fill _tmp32 to $t1 from $fp-148
	  mul $t2, $t0, $t1	
	  sw $t2, -184($fp)	# spill _tmp41 from $t2 to $fp-184
	# _tmp42 = y + _tmp41
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t1, -184($fp)	# fill _tmp41 to $t1 from $fp-184
	  add $t2, $t0, $t1	
	  sw $t2, -188($fp)	# spill _tmp42 from $t2 to $fp-188
	# _tmp43 = 34
	  li $t2, 34		# load constant value 34 into $t2
	  sw $t2, -192($fp)	# spill _tmp43 from $t2 to $fp-192
	# *(_tmp42) = _tmp43
	  lw $t0, -192($fp)	# fill _tmp43 to $t0 from $fp-192
	  lw $t2, -188($fp)	# fill _tmp42 to $t2 from $fp-188
	  sw $t0, 0($t2) 	# store with offset
	# _tmp44 = 3
	  li $t2, 3		# load constant value 3 into $t2
	  sw $t2, -196($fp)	# spill _tmp44 from $t2 to $fp-196
	# _tmp45 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -200($fp)	# spill _tmp45 from $t2 to $fp-200
	# _tmp46 = _tmp44 < _tmp45
	  lw $t0, -196($fp)	# fill _tmp44 to $t0 from $fp-196
	  lw $t1, -200($fp)	# fill _tmp45 to $t1 from $fp-200
	  slt $t2, $t0, $t1	
	  sw $t2, -204($fp)	# spill _tmp46 from $t2 to $fp-204
	# _tmp47 = *(x + -4)
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -208($fp)	# spill _tmp47 from $t2 to $fp-208
	# _tmp48 = _tmp44 < _tmp47
	  lw $t0, -196($fp)	# fill _tmp44 to $t0 from $fp-196
	  lw $t1, -208($fp)	# fill _tmp47 to $t1 from $fp-208
	  slt $t2, $t0, $t1	
	  sw $t2, -212($fp)	# spill _tmp48 from $t2 to $fp-212
	# _tmp49 = _tmp48 == _tmp45
	  lw $t0, -212($fp)	# fill _tmp48 to $t0 from $fp-212
	  lw $t1, -200($fp)	# fill _tmp45 to $t1 from $fp-200
	  seq $t2, $t0, $t1	
	  sw $t2, -216($fp)	# spill _tmp49 from $t2 to $fp-216
	# _tmp50 = _tmp46 || _tmp49
	  lw $t0, -204($fp)	# fill _tmp46 to $t0 from $fp-204
	  lw $t1, -216($fp)	# fill _tmp49 to $t1 from $fp-216
	  or $t2, $t0, $t1	
	  sw $t2, -220($fp)	# spill _tmp50 from $t2 to $fp-220
	# IfZ _tmp50 Goto _L4
	  lw $t0, -220($fp)	# fill _tmp50 to $t0 from $fp-220
	  beqz $t0, _L4	# branch if _tmp50 is zero 
	# _tmp51 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string5: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string5	# load label
	  sw $t2, -224($fp)	# spill _tmp51 from $t2 to $fp-224
	# PushParam _tmp51
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -224($fp)	# fill _tmp51 to $t0 from $fp-224
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L4:
	# _tmp52 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -228($fp)	# spill _tmp52 from $t2 to $fp-228
	# _tmp53 = _tmp52 * _tmp44
	  lw $t0, -228($fp)	# fill _tmp52 to $t0 from $fp-228
	  lw $t1, -196($fp)	# fill _tmp44 to $t1 from $fp-196
	  mul $t2, $t0, $t1	
	  sw $t2, -232($fp)	# spill _tmp53 from $t2 to $fp-232
	# _tmp54 = x + _tmp53
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t1, -232($fp)	# fill _tmp53 to $t1 from $fp-232
	  add $t2, $t0, $t1	
	  sw $t2, -236($fp)	# spill _tmp54 from $t2 to $fp-236
	# _tmp55 = *(_tmp54)
	  lw $t0, -236($fp)	# fill _tmp54 to $t0 from $fp-236
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -240($fp)	# spill _tmp55 from $t2 to $fp-240
	# PushParam _tmp55
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -240($fp)	# fill _tmp55 to $t0 from $fp-240
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp56 = "\n"
	  .data			# create string constant marked with label
	  _string6: .asciiz "\n"
	  .text
	  la $t2, _string6	# load label
	  sw $t2, -244($fp)	# spill _tmp56 from $t2 to $fp-244
	# PushParam _tmp56
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -244($fp)	# fill _tmp56 to $t0 from $fp-244
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp57 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -248($fp)	# spill _tmp57 from $t2 to $fp-248
	# _tmp58 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -252($fp)	# spill _tmp58 from $t2 to $fp-252
	# _tmp59 = _tmp57 < _tmp58
	  lw $t0, -248($fp)	# fill _tmp57 to $t0 from $fp-248
	  lw $t1, -252($fp)	# fill _tmp58 to $t1 from $fp-252
	  slt $t2, $t0, $t1	
	  sw $t2, -256($fp)	# spill _tmp59 from $t2 to $fp-256
	# _tmp60 = *(y + -4)
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -260($fp)	# spill _tmp60 from $t2 to $fp-260
	# _tmp61 = _tmp57 < _tmp60
	  lw $t0, -248($fp)	# fill _tmp57 to $t0 from $fp-248
	  lw $t1, -260($fp)	# fill _tmp60 to $t1 from $fp-260
	  slt $t2, $t0, $t1	
	  sw $t2, -264($fp)	# spill _tmp61 from $t2 to $fp-264
	# _tmp62 = _tmp61 == _tmp58
	  lw $t0, -264($fp)	# fill _tmp61 to $t0 from $fp-264
	  lw $t1, -252($fp)	# fill _tmp58 to $t1 from $fp-252
	  seq $t2, $t0, $t1	
	  sw $t2, -268($fp)	# spill _tmp62 from $t2 to $fp-268
	# _tmp63 = _tmp59 || _tmp62
	  lw $t0, -256($fp)	# fill _tmp59 to $t0 from $fp-256
	  lw $t1, -268($fp)	# fill _tmp62 to $t1 from $fp-268
	  or $t2, $t0, $t1	
	  sw $t2, -272($fp)	# spill _tmp63 from $t2 to $fp-272
	# IfZ _tmp63 Goto _L5
	  lw $t0, -272($fp)	# fill _tmp63 to $t0 from $fp-272
	  beqz $t0, _L5	# branch if _tmp63 is zero 
	# _tmp64 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string7: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string7	# load label
	  sw $t2, -276($fp)	# spill _tmp64 from $t2 to $fp-276
	# PushParam _tmp64
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -276($fp)	# fill _tmp64 to $t0 from $fp-276
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L5:
	# _tmp65 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -280($fp)	# spill _tmp65 from $t2 to $fp-280
	# _tmp66 = _tmp65 * _tmp57
	  lw $t0, -280($fp)	# fill _tmp65 to $t0 from $fp-280
	  lw $t1, -248($fp)	# fill _tmp57 to $t1 from $fp-248
	  mul $t2, $t0, $t1	
	  sw $t2, -284($fp)	# spill _tmp66 from $t2 to $fp-284
	# _tmp67 = y + _tmp66
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t1, -284($fp)	# fill _tmp66 to $t1 from $fp-284
	  add $t2, $t0, $t1	
	  sw $t2, -288($fp)	# spill _tmp67 from $t2 to $fp-288
	# _tmp68 = *(_tmp67)
	  lw $t0, -288($fp)	# fill _tmp67 to $t0 from $fp-288
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -292($fp)	# spill _tmp68 from $t2 to $fp-292
	# PushParam _tmp68
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -292($fp)	# fill _tmp68 to $t0 from $fp-292
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp69 = "\n"
	  .data			# create string constant marked with label
	  _string8: .asciiz "\n"
	  .text
	  la $t2, _string8	# load label
	  sw $t2, -296($fp)	# spill _tmp69 from $t2 to $fp-296
	# PushParam _tmp69
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -296($fp)	# fill _tmp69 to $t0 from $fp-296
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp70 = 3
	  li $t2, 3		# load constant value 3 into $t2
	  sw $t2, -300($fp)	# spill _tmp70 from $t2 to $fp-300
	# _tmp71 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -304($fp)	# spill _tmp71 from $t2 to $fp-304
	# _tmp72 = _tmp70 < _tmp71
	  lw $t0, -300($fp)	# fill _tmp70 to $t0 from $fp-300
	  lw $t1, -304($fp)	# fill _tmp71 to $t1 from $fp-304
	  slt $t2, $t0, $t1	
	  sw $t2, -308($fp)	# spill _tmp72 from $t2 to $fp-308
	# _tmp73 = *(x + -4)
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -312($fp)	# spill _tmp73 from $t2 to $fp-312
	# _tmp74 = _tmp70 < _tmp73
	  lw $t0, -300($fp)	# fill _tmp70 to $t0 from $fp-300
	  lw $t1, -312($fp)	# fill _tmp73 to $t1 from $fp-312
	  slt $t2, $t0, $t1	
	  sw $t2, -316($fp)	# spill _tmp74 from $t2 to $fp-316
	# _tmp75 = _tmp74 == _tmp71
	  lw $t0, -316($fp)	# fill _tmp74 to $t0 from $fp-316
	  lw $t1, -304($fp)	# fill _tmp71 to $t1 from $fp-304
	  seq $t2, $t0, $t1	
	  sw $t2, -320($fp)	# spill _tmp75 from $t2 to $fp-320
	# _tmp76 = _tmp72 || _tmp75
	  lw $t0, -308($fp)	# fill _tmp72 to $t0 from $fp-308
	  lw $t1, -320($fp)	# fill _tmp75 to $t1 from $fp-320
	  or $t2, $t0, $t1	
	  sw $t2, -324($fp)	# spill _tmp76 from $t2 to $fp-324
	# IfZ _tmp76 Goto _L6
	  lw $t0, -324($fp)	# fill _tmp76 to $t0 from $fp-324
	  beqz $t0, _L6	# branch if _tmp76 is zero 
	# _tmp77 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string9: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string9	# load label
	  sw $t2, -328($fp)	# spill _tmp77 from $t2 to $fp-328
	# PushParam _tmp77
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -328($fp)	# fill _tmp77 to $t0 from $fp-328
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L6:
	# _tmp78 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -332($fp)	# spill _tmp78 from $t2 to $fp-332
	# _tmp79 = _tmp78 * _tmp70
	  lw $t0, -332($fp)	# fill _tmp78 to $t0 from $fp-332
	  lw $t1, -300($fp)	# fill _tmp70 to $t1 from $fp-300
	  mul $t2, $t0, $t1	
	  sw $t2, -336($fp)	# spill _tmp79 from $t2 to $fp-336
	# _tmp80 = x + _tmp79
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t1, -336($fp)	# fill _tmp79 to $t1 from $fp-336
	  add $t2, $t0, $t1	
	  sw $t2, -340($fp)	# spill _tmp80 from $t2 to $fp-340
	# _tmp81 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -344($fp)	# spill _tmp81 from $t2 to $fp-344
	# _tmp82 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -348($fp)	# spill _tmp82 from $t2 to $fp-348
	# _tmp83 = _tmp81 < _tmp82
	  lw $t0, -344($fp)	# fill _tmp81 to $t0 from $fp-344
	  lw $t1, -348($fp)	# fill _tmp82 to $t1 from $fp-348
	  slt $t2, $t0, $t1	
	  sw $t2, -352($fp)	# spill _tmp83 from $t2 to $fp-352
	# _tmp84 = *(y + -4)
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -356($fp)	# spill _tmp84 from $t2 to $fp-356
	# _tmp85 = _tmp81 < _tmp84
	  lw $t0, -344($fp)	# fill _tmp81 to $t0 from $fp-344
	  lw $t1, -356($fp)	# fill _tmp84 to $t1 from $fp-356
	  slt $t2, $t0, $t1	
	  sw $t2, -360($fp)	# spill _tmp85 from $t2 to $fp-360
	# _tmp86 = _tmp85 == _tmp82
	  lw $t0, -360($fp)	# fill _tmp85 to $t0 from $fp-360
	  lw $t1, -348($fp)	# fill _tmp82 to $t1 from $fp-348
	  seq $t2, $t0, $t1	
	  sw $t2, -364($fp)	# spill _tmp86 from $t2 to $fp-364
	# _tmp87 = _tmp83 || _tmp86
	  lw $t0, -352($fp)	# fill _tmp83 to $t0 from $fp-352
	  lw $t1, -364($fp)	# fill _tmp86 to $t1 from $fp-364
	  or $t2, $t0, $t1	
	  sw $t2, -368($fp)	# spill _tmp87 from $t2 to $fp-368
	# IfZ _tmp87 Goto _L7
	  lw $t0, -368($fp)	# fill _tmp87 to $t0 from $fp-368
	  beqz $t0, _L7	# branch if _tmp87 is zero 
	# _tmp88 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string10: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string10	# load label
	  sw $t2, -372($fp)	# spill _tmp88 from $t2 to $fp-372
	# PushParam _tmp88
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -372($fp)	# fill _tmp88 to $t0 from $fp-372
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L7:
	# _tmp89 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -376($fp)	# spill _tmp89 from $t2 to $fp-376
	# _tmp90 = _tmp89 * _tmp81
	  lw $t0, -376($fp)	# fill _tmp89 to $t0 from $fp-376
	  lw $t1, -344($fp)	# fill _tmp81 to $t1 from $fp-344
	  mul $t2, $t0, $t1	
	  sw $t2, -380($fp)	# spill _tmp90 from $t2 to $fp-380
	# _tmp91 = y + _tmp90
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t1, -380($fp)	# fill _tmp90 to $t1 from $fp-380
	  add $t2, $t0, $t1	
	  sw $t2, -384($fp)	# spill _tmp91 from $t2 to $fp-384
	# _tmp92 = *(_tmp91)
	  lw $t0, -384($fp)	# fill _tmp91 to $t0 from $fp-384
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -388($fp)	# spill _tmp92 from $t2 to $fp-388
	# *(_tmp80) = _tmp92
	  lw $t0, -388($fp)	# fill _tmp92 to $t0 from $fp-388
	  lw $t2, -340($fp)	# fill _tmp80 to $t2 from $fp-340
	  sw $t0, 0($t2) 	# store with offset
	# _tmp93 = 3
	  li $t2, 3		# load constant value 3 into $t2
	  sw $t2, -392($fp)	# spill _tmp93 from $t2 to $fp-392
	# _tmp94 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -396($fp)	# spill _tmp94 from $t2 to $fp-396
	# _tmp95 = _tmp93 < _tmp94
	  lw $t0, -392($fp)	# fill _tmp93 to $t0 from $fp-392
	  lw $t1, -396($fp)	# fill _tmp94 to $t1 from $fp-396
	  slt $t2, $t0, $t1	
	  sw $t2, -400($fp)	# spill _tmp95 from $t2 to $fp-400
	# _tmp96 = *(x + -4)
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -404($fp)	# spill _tmp96 from $t2 to $fp-404
	# _tmp97 = _tmp93 < _tmp96
	  lw $t0, -392($fp)	# fill _tmp93 to $t0 from $fp-392
	  lw $t1, -404($fp)	# fill _tmp96 to $t1 from $fp-404
	  slt $t2, $t0, $t1	
	  sw $t2, -408($fp)	# spill _tmp97 from $t2 to $fp-408
	# _tmp98 = _tmp97 == _tmp94
	  lw $t0, -408($fp)	# fill _tmp97 to $t0 from $fp-408
	  lw $t1, -396($fp)	# fill _tmp94 to $t1 from $fp-396
	  seq $t2, $t0, $t1	
	  sw $t2, -412($fp)	# spill _tmp98 from $t2 to $fp-412
	# _tmp99 = _tmp95 || _tmp98
	  lw $t0, -400($fp)	# fill _tmp95 to $t0 from $fp-400
	  lw $t1, -412($fp)	# fill _tmp98 to $t1 from $fp-412
	  or $t2, $t0, $t1	
	  sw $t2, -416($fp)	# spill _tmp99 from $t2 to $fp-416
	# IfZ _tmp99 Goto _L8
	  lw $t0, -416($fp)	# fill _tmp99 to $t0 from $fp-416
	  beqz $t0, _L8	# branch if _tmp99 is zero 
	# _tmp100 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string11: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string11	# load label
	  sw $t2, -420($fp)	# spill _tmp100 from $t2 to $fp-420
	# PushParam _tmp100
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -420($fp)	# fill _tmp100 to $t0 from $fp-420
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L8:
	# _tmp101 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -424($fp)	# spill _tmp101 from $t2 to $fp-424
	# _tmp102 = _tmp101 * _tmp93
	  lw $t0, -424($fp)	# fill _tmp101 to $t0 from $fp-424
	  lw $t1, -392($fp)	# fill _tmp93 to $t1 from $fp-392
	  mul $t2, $t0, $t1	
	  sw $t2, -428($fp)	# spill _tmp102 from $t2 to $fp-428
	# _tmp103 = x + _tmp102
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t1, -428($fp)	# fill _tmp102 to $t1 from $fp-428
	  add $t2, $t0, $t1	
	  sw $t2, -432($fp)	# spill _tmp103 from $t2 to $fp-432
	# _tmp104 = *(_tmp103)
	  lw $t0, -432($fp)	# fill _tmp103 to $t0 from $fp-432
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -436($fp)	# spill _tmp104 from $t2 to $fp-436
	# PushParam _tmp104
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -436($fp)	# fill _tmp104 to $t0 from $fp-436
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp105 = "\n"
	  .data			# create string constant marked with label
	  _string12: .asciiz "\n"
	  .text
	  la $t2, _string12	# load label
	  sw $t2, -440($fp)	# spill _tmp105 from $t2 to $fp-440
	# PushParam _tmp105
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -440($fp)	# fill _tmp105 to $t0 from $fp-440
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp106 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -444($fp)	# spill _tmp106 from $t2 to $fp-444
	# _tmp107 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -448($fp)	# spill _tmp107 from $t2 to $fp-448
	# _tmp108 = _tmp106 < _tmp107
	  lw $t0, -444($fp)	# fill _tmp106 to $t0 from $fp-444
	  lw $t1, -448($fp)	# fill _tmp107 to $t1 from $fp-448
	  slt $t2, $t0, $t1	
	  sw $t2, -452($fp)	# spill _tmp108 from $t2 to $fp-452
	# _tmp109 = *(y + -4)
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -456($fp)	# spill _tmp109 from $t2 to $fp-456
	# _tmp110 = _tmp106 < _tmp109
	  lw $t0, -444($fp)	# fill _tmp106 to $t0 from $fp-444
	  lw $t1, -456($fp)	# fill _tmp109 to $t1 from $fp-456
	  slt $t2, $t0, $t1	
	  sw $t2, -460($fp)	# spill _tmp110 from $t2 to $fp-460
	# _tmp111 = _tmp110 == _tmp107
	  lw $t0, -460($fp)	# fill _tmp110 to $t0 from $fp-460
	  lw $t1, -448($fp)	# fill _tmp107 to $t1 from $fp-448
	  seq $t2, $t0, $t1	
	  sw $t2, -464($fp)	# spill _tmp111 from $t2 to $fp-464
	# _tmp112 = _tmp108 || _tmp111
	  lw $t0, -452($fp)	# fill _tmp108 to $t0 from $fp-452
	  lw $t1, -464($fp)	# fill _tmp111 to $t1 from $fp-464
	  or $t2, $t0, $t1	
	  sw $t2, -468($fp)	# spill _tmp112 from $t2 to $fp-468
	# IfZ _tmp112 Goto _L9
	  lw $t0, -468($fp)	# fill _tmp112 to $t0 from $fp-468
	  beqz $t0, _L9	# branch if _tmp112 is zero 
	# _tmp113 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string13: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string13	# load label
	  sw $t2, -472($fp)	# spill _tmp113 from $t2 to $fp-472
	# PushParam _tmp113
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -472($fp)	# fill _tmp113 to $t0 from $fp-472
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L9:
	# _tmp114 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -476($fp)	# spill _tmp114 from $t2 to $fp-476
	# _tmp115 = _tmp114 * _tmp106
	  lw $t0, -476($fp)	# fill _tmp114 to $t0 from $fp-476
	  lw $t1, -444($fp)	# fill _tmp106 to $t1 from $fp-444
	  mul $t2, $t0, $t1	
	  sw $t2, -480($fp)	# spill _tmp115 from $t2 to $fp-480
	# _tmp116 = y + _tmp115
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t1, -480($fp)	# fill _tmp115 to $t1 from $fp-480
	  add $t2, $t0, $t1	
	  sw $t2, -484($fp)	# spill _tmp116 from $t2 to $fp-484
	# _tmp117 = *(_tmp116)
	  lw $t0, -484($fp)	# fill _tmp116 to $t0 from $fp-484
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -488($fp)	# spill _tmp117 from $t2 to $fp-488
	# PushParam _tmp117
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -488($fp)	# fill _tmp117 to $t0 from $fp-488
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp118 = "\n"
	  .data			# create string constant marked with label
	  _string14: .asciiz "\n"
	  .text
	  la $t2, _string14	# load label
	  sw $t2, -492($fp)	# spill _tmp118 from $t2 to $fp-492
	# PushParam _tmp118
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -492($fp)	# fill _tmp118 to $t0 from $fp-492
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp119 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -496($fp)	# spill _tmp119 from $t2 to $fp-496
	# _tmp120 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -500($fp)	# spill _tmp120 from $t2 to $fp-500
	# _tmp121 = _tmp119 < _tmp120
	  lw $t0, -496($fp)	# fill _tmp119 to $t0 from $fp-496
	  lw $t1, -500($fp)	# fill _tmp120 to $t1 from $fp-500
	  slt $t2, $t0, $t1	
	  sw $t2, -504($fp)	# spill _tmp121 from $t2 to $fp-504
	# _tmp122 = *(y + -4)
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -508($fp)	# spill _tmp122 from $t2 to $fp-508
	# _tmp123 = _tmp119 < _tmp122
	  lw $t0, -496($fp)	# fill _tmp119 to $t0 from $fp-496
	  lw $t1, -508($fp)	# fill _tmp122 to $t1 from $fp-508
	  slt $t2, $t0, $t1	
	  sw $t2, -512($fp)	# spill _tmp123 from $t2 to $fp-512
	# _tmp124 = _tmp123 == _tmp120
	  lw $t0, -512($fp)	# fill _tmp123 to $t0 from $fp-512
	  lw $t1, -500($fp)	# fill _tmp120 to $t1 from $fp-500
	  seq $t2, $t0, $t1	
	  sw $t2, -516($fp)	# spill _tmp124 from $t2 to $fp-516
	# _tmp125 = _tmp121 || _tmp124
	  lw $t0, -504($fp)	# fill _tmp121 to $t0 from $fp-504
	  lw $t1, -516($fp)	# fill _tmp124 to $t1 from $fp-516
	  or $t2, $t0, $t1	
	  sw $t2, -520($fp)	# spill _tmp125 from $t2 to $fp-520
	# IfZ _tmp125 Goto _L10
	  lw $t0, -520($fp)	# fill _tmp125 to $t0 from $fp-520
	  beqz $t0, _L10	# branch if _tmp125 is zero 
	# _tmp126 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string15: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string15	# load label
	  sw $t2, -524($fp)	# spill _tmp126 from $t2 to $fp-524
	# PushParam _tmp126
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -524($fp)	# fill _tmp126 to $t0 from $fp-524
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L10:
	# _tmp127 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -528($fp)	# spill _tmp127 from $t2 to $fp-528
	# _tmp128 = _tmp127 * _tmp119
	  lw $t0, -528($fp)	# fill _tmp127 to $t0 from $fp-528
	  lw $t1, -496($fp)	# fill _tmp119 to $t1 from $fp-496
	  mul $t2, $t0, $t1	
	  sw $t2, -532($fp)	# spill _tmp128 from $t2 to $fp-532
	# _tmp129 = y + _tmp128
	  lw $t0, -12($fp)	# fill y to $t0 from $fp-12
	  lw $t1, -532($fp)	# fill _tmp128 to $t1 from $fp-532
	  add $t2, $t0, $t1	
	  sw $t2, -536($fp)	# spill _tmp129 from $t2 to $fp-536
	# _tmp130 = *(_tmp129)
	  lw $t0, -536($fp)	# fill _tmp129 to $t0 from $fp-536
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -540($fp)	# spill _tmp130 from $t2 to $fp-540
	# q = _tmp130
	  lw $t2, -540($fp)	# fill _tmp130 to $t2 from $fp-540
	  sw $t2, -16($fp)	# spill q from $t2 to $fp-16
	# PushParam q
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -16($fp)	# fill q to $t0 from $fp-16
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp131 = "\n"
	  .data			# create string constant marked with label
	  _string16: .asciiz "\n"
	  .text
	  la $t2, _string16	# load label
	  sw $t2, -544($fp)	# spill _tmp131 from $t2 to $fp-544
	# PushParam _tmp131
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -544($fp)	# fill _tmp131 to $t0 from $fp-544
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp132 = 3
	  li $t2, 3		# load constant value 3 into $t2
	  sw $t2, -548($fp)	# spill _tmp132 from $t2 to $fp-548
	# _tmp133 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -552($fp)	# spill _tmp133 from $t2 to $fp-552
	# _tmp134 = _tmp132 < _tmp133
	  lw $t0, -548($fp)	# fill _tmp132 to $t0 from $fp-548
	  lw $t1, -552($fp)	# fill _tmp133 to $t1 from $fp-552
	  slt $t2, $t0, $t1	
	  sw $t2, -556($fp)	# spill _tmp134 from $t2 to $fp-556
	# _tmp135 = *(x + -4)
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t2, -4($t0) 	# load with offset
	  sw $t2, -560($fp)	# spill _tmp135 from $t2 to $fp-560
	# _tmp136 = _tmp132 < _tmp135
	  lw $t0, -548($fp)	# fill _tmp132 to $t0 from $fp-548
	  lw $t1, -560($fp)	# fill _tmp135 to $t1 from $fp-560
	  slt $t2, $t0, $t1	
	  sw $t2, -564($fp)	# spill _tmp136 from $t2 to $fp-564
	# _tmp137 = _tmp136 == _tmp133
	  lw $t0, -564($fp)	# fill _tmp136 to $t0 from $fp-564
	  lw $t1, -552($fp)	# fill _tmp133 to $t1 from $fp-552
	  seq $t2, $t0, $t1	
	  sw $t2, -568($fp)	# spill _tmp137 from $t2 to $fp-568
	# _tmp138 = _tmp134 || _tmp137
	  lw $t0, -556($fp)	# fill _tmp134 to $t0 from $fp-556
	  lw $t1, -568($fp)	# fill _tmp137 to $t1 from $fp-568
	  or $t2, $t0, $t1	
	  sw $t2, -572($fp)	# spill _tmp138 from $t2 to $fp-572
	# IfZ _tmp138 Goto _L11
	  lw $t0, -572($fp)	# fill _tmp138 to $t0 from $fp-572
	  beqz $t0, _L11	# branch if _tmp138 is zero 
	# _tmp139 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string17: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string17	# load label
	  sw $t2, -576($fp)	# spill _tmp139 from $t2 to $fp-576
	# PushParam _tmp139
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -576($fp)	# fill _tmp139 to $t0 from $fp-576
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L11:
	# _tmp140 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -580($fp)	# spill _tmp140 from $t2 to $fp-580
	# _tmp141 = _tmp140 * _tmp132
	  lw $t0, -580($fp)	# fill _tmp140 to $t0 from $fp-580
	  lw $t1, -548($fp)	# fill _tmp132 to $t1 from $fp-548
	  mul $t2, $t0, $t1	
	  sw $t2, -584($fp)	# spill _tmp141 from $t2 to $fp-584
	# _tmp142 = x + _tmp141
	  lw $t0, -8($fp)	# fill x to $t0 from $fp-8
	  lw $t1, -584($fp)	# fill _tmp141 to $t1 from $fp-584
	  add $t2, $t0, $t1	
	  sw $t2, -588($fp)	# spill _tmp142 from $t2 to $fp-588
	# _tmp143 = *(_tmp142)
	  lw $t0, -588($fp)	# fill _tmp142 to $t0 from $fp-588
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -592($fp)	# spill _tmp143 from $t2 to $fp-592
	# _tmp144 = 23
	  li $t2, 23		# load constant value 23 into $t2
	  sw $t2, -596($fp)	# spill _tmp144 from $t2 to $fp-596
	# _tmp145 = _tmp143 + _tmp144
	  lw $t0, -592($fp)	# fill _tmp143 to $t0 from $fp-592
	  lw $t1, -596($fp)	# fill _tmp144 to $t1 from $fp-596
	  add $t2, $t0, $t1	
	  sw $t2, -600($fp)	# spill _tmp145 from $t2 to $fp-600
	# q = _tmp145
	  lw $t2, -600($fp)	# fill _tmp145 to $t2 from $fp-600
	  sw $t2, -16($fp)	# spill q from $t2 to $fp-16
	# PushParam q
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -16($fp)	# fill q to $t0 from $fp-16
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp146 = "\n"
	  .data			# create string constant marked with label
	  _string18: .asciiz "\n"
	  .text
	  la $t2, _string18	# load label
	  sw $t2, -604($fp)	# spill _tmp146 from $t2 to $fp-604
	# PushParam _tmp146
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -604($fp)	# fill _tmp146 to $t0 from $fp-604
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
_PrintInt:
        subu $sp, $sp, 8
        sw $fp, 8($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 8
        li   $v0, 1
        lw   $a0, 4($fp)
        syscall
        move $sp, $fp
        lw $ra, -4($fp)
        lw $fp, 0($fp)
        jr $ra
                                
_PrintString:
        subu $sp, $sp, 8
        sw $fp, 8($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 8
        li   $v0, 4
        lw $a0, 4($fp)
        syscall
        move $sp, $fp
        lw $ra, -4($fp)
        lw $fp, 0($fp)
        jr $ra
        
_PrintBool:
	subu $sp, $sp, 8
	sw $fp, 8($sp)
	sw $ra, 4($sp)
        addiu $fp, $sp, 8
	lw $t1, 4($fp)
	blez $t1, fbr
	li   $v0, 4		# system call for print_str
	la   $a0, TRUE		# address of str to print
	syscall			
	b end
fbr:	li   $v0, 4		# system call for print_str
	la   $a0, FALSE		# address of str to print
	syscall				
end:	move $sp, $fp
	lw $ra, -4($fp)
	lw $fp, 0($fp)
	jr $ra

_Alloc:
        subu $sp, $sp, 8
        sw $fp, 8($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 8
        li   $v0, 9
        lw $a0, 4($fp)
	syscall
        move $sp, $fp
        lw $ra, -4($fp)
        lw $fp, 0($fp) 
        jr $ra


_StringEqual:
	subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	sw $fp, 8($sp)        # save fp
	sw $ra, 4($sp)        # save ra
	addiu $fp, $sp, 8     # set up new fp
	subu $sp, $sp, 4      # decrement sp to make space for locals/temps

	li $v0,0

	#Determine length string 1
	lw $t0, 4($fp)       
	li $t3,0
bloop1: 
	lb $t5, ($t0) 
	beqz $t5, eloop1	
	addi $t0, 1
	addi $t3, 1
	b bloop1
eloop1:

	#Determine length string 2
	lw $t1, 8($fp)
	li $t4,0
bloop2: 
	lb $t5, ($t1) 
	beqz $t5, eloop2	
	addi $t1, 1
	addi $t4, 1
	b bloop2
eloop2:
	bne $t3,$t4,end1       #Check String Lengths Same

	lw $t0, 4($fp)       
	lw $t1, 8($fp)
	li $t3, 0     		
bloop3:	
	lb $t5, ($t0) 
	lb $t6, ($t1) 
	bne $t5, $t6, end1
	addi $t3, 1
	addi $t0, 1
	addi $t1, 1
	bne $t3,$t4,bloop3
eloop3:	li $v0,1

end1:	move $sp, $fp         # pop callee frame off stack
	lw $ra, -4($fp)       # restore saved ra
	lw $fp, 0($fp)        # restore saved fp
	jr $ra                # return from function

_Halt:
        li $v0, 10
        syscall

_ReadInteger:
	subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	sw $fp, 8($sp)        # save fp
	sw $ra, 4($sp)        # save ra
	addiu $fp, $sp, 8     # set up new fp
	subu $sp, $sp, 4      # decrement sp to make space for locals/temps
	li $v0, 5
	syscall
	move $sp, $fp         # pop callee frame off stack
	lw $ra, -4($fp)       # restore saved ra
	lw $fp, 0($fp)        # restore saved fp
	jr $ra
        

_ReadLine:
	subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	sw $fp, 8($sp)        # save fp
	sw $ra, 4($sp)        # save ra
	addiu $fp, $sp, 8     # set up new fp
	subu $sp, $sp, 4      # decrement sp to make space for locals/temps
	li $a1, 40
	la $a0, SPACE
	li $v0, 8
	syscall

	la $t1, SPACE
bloop4: 
	lb $t5, ($t1) 
	beqz $t5, eloop4	
	addi $t1, 1
	b bloop4
eloop4:
	addi $t1,-1
	li $t6,0
        sb $t6, ($t1)

	la $v0, SPACE
	move $sp, $fp         # pop callee frame off stack
	lw $ra, -4($fp)       # restore saved ra
	lw $fp, 0($fp)        # restore saved fp
	jr $ra
	

	.data
TRUE:.asciiz "true"
FALSE:.asciiz "false"
SPACE:.asciiz "Making Space For Inputed Values Is Fun."
