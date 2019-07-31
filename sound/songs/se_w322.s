	.include "MPlayDef.s"

	.equ	se_w322_grp, voicegroup128
	.equ	se_w322_pri, 4
	.equ	se_w322_rev, reverb_set+50
	.equ	se_w322_mvl, 127
	.equ	se_w322_key, 0
	.equ	se_w322_tbs, 1
	.equ	se_w322_exg, 0
	.equ	se_w322_cmp, 1

	.section .rodata
	.global	se_w322
	.align	2



se_w322_1:
	.byte	KEYSH , se_w322_key+0
	.byte	TEMPO , 150*se_w322_tbs/2
	.byte		VOICE , 46
	.byte		BENDR , 12
	.byte		PAN   , c_v+0
	.byte		VOL   , 110*se_w322_mvl/mxv
	.byte		BEND  , c_v-4
	.byte		N09   , As5 , v112
	.byte	W06
	.byte	W03
	.byte		PAN   , c_v-5
	.byte		N08   , Cn5 
	.byte	W03
	.byte	W06
	.byte		PAN   , c_v-9
	.byte		N10   , Gn5 
	.byte	W06
	.byte	W04
	.byte		PAN   , c_v-5
	.byte		N09   , Fn6 
	.byte	W02
	.byte	W06
	.byte	W02
	.byte		PAN   , c_v+0
	.byte		N09   , An5 
	.byte	W04
	.byte	W06
	.byte		PAN   , c_v+4
	.byte		N09   , As5 
	.byte	W06
	.byte	W03
	.byte		PAN   , c_v+9
	.byte		N08   , Cn5 , v108
	.byte	W03
	.byte	W06
	.byte		PAN   , c_v+4
	.byte		N10   , Gn5 , v104
	.byte	W06
	.byte	W04
	.byte		PAN   , c_v+0
	.byte		N09   , Fn6 , v096
	.byte	W02
	.byte	W06
	.byte	W02
	.byte		PAN   , c_v-5
	.byte		N09   , An5 , v092
	.byte	W04
	.byte	W04
	.byte		PAN   , c_v-9
	.byte	W02
	.byte		N09   , As5 , v084
	.byte	W06
	.byte	W03
	.byte		PAN   , c_v-5
	.byte		N08   , Cn5 , v080
	.byte	W03
	.byte	W06
	.byte		N10   , Gn5 , v072
	.byte	W01
	.byte		PAN   , c_v+0
	.byte	W05
	.byte	W04
	.byte		        c_v+4
	.byte		N09   , Fn6 , v068
	.byte	W02
	.byte	W06
	.byte	W02
	.byte		PAN   , c_v+9
	.byte		N09   , An5 , v060
	.byte	W04
	.byte	W04
	.byte		PAN   , c_v+4
	.byte	W02
	.byte		N09   , As5 , v056
	.byte	W06
	.byte	W03
	.byte		PAN   , c_v+0
	.byte		N08   , Cn5 , v052
	.byte	W03
	.byte	W06
	.byte		N10   , Gn5 , v044
	.byte	W01
	.byte		PAN   , c_v-5
	.byte	W05
	.byte	W03
	.byte		        c_v-9
	.byte	W01
	.byte		N09   , Fn6 , v040
	.byte	W02
	.byte	W06
	.byte	W02
	.byte		PAN   , c_v-5
	.byte		N09   , An5 , v032
	.byte	W04
	.byte	W06
	.byte		PAN   , c_v+0
	.byte	W06
	.byte	FINE



se_w322_2:
	.byte	KEYSH , se_w322_key+0
	.byte		VOICE , 53
	.byte		XCMD  , xIECV , 9
	.byte		        xIECL , 8
	.byte		VOL   , 43*se_w322_mvl/mxv
	.byte		BEND  , c_v-2
	.byte	W04
	.byte		N08   , Fn5 , v112
	.byte	W02
	.byte	W06
	.byte	W01
	.byte		N10   , Ds5 
	.byte	W05
	.byte	W06
	.byte		N09   , As6 
	.byte	W06
	.byte	W03
	.byte		        Cn6 
	.byte	W03
	.byte	W06
	.byte		N10   , Fn5 
	.byte	W06
	.byte	W04
	.byte		N08   
	.byte	W02
	.byte	W06
	.byte	W01
	.byte		N10   , Ds5 , v104
	.byte	W05
	.byte	W06
	.byte		N09   , As6 , v100
	.byte	W06
	.byte	W03
	.byte		        Cn6 , v092
	.byte	W03
	.byte	W06
	.byte		N10   , Fn5 , v088
	.byte	W06
	.byte	W04
	.byte		N08   , Fn5 , v080
	.byte	W02
	.byte	W06
	.byte	W01
	.byte		N10   , Ds5 , v076
	.byte	W05
	.byte	W06
	.byte		N09   , As6 , v072
	.byte	W06
	.byte	W03
	.byte		        Cn6 , v064
	.byte	W03
	.byte	W06
	.byte		N10   , Fn5 , v060
	.byte	W06
	.byte	W04
	.byte		N08   , Fn5 , v052
	.byte	W02
	.byte	W06
	.byte	W01
	.byte		N10   , Ds5 , v048
	.byte	W05
	.byte	W06
	.byte		N09   , As6 , v040
	.byte	W06
	.byte	W03
	.byte		        Cn6 , v036
	.byte	W03
	.byte	W06
	.byte		N12   , Fn5 , v032
	.byte	W06
	.byte	W06
	.byte	FINE


	.align	2

se_w322:
	.byte	2	
	.byte	0	
	.byte	se_w322_pri	
	.byte	se_w322_rev	

	.word	se_w322_grp

	.word	se_w322_1
	.word	se_w322_2

	.end
