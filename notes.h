#pragma once


/*
 supported vowels
unicode  IPA glyph  pronunciation
0x0069   i	        eas_y_
0x0079   y	        d_uu_r (dutch)			
0x0268   ɨ          l_i_p
0x0289   ʉ			g_oo_se 	
0x026F   ɯ          h_oo_k	
0x0075   u          d_o_
0x026A   ɪ	        c_i_ty
0x028F   ʏ          Gl_u_ck (german)
0x028A   ʊ          p_u_t
0x0065   e	        l_e_gen (dutch)
0x00F8   ø	        d_e_ur  (dutch)		
0x0258   ɘ	        n_u_t
0x0275   ɵ			f_u_ll  (swedish)
0x0264   ɤ	        f_oo_t
0x006f   o          M_o_tiv (german)
0x0259   ə          _a_bout
0x025B   ɛ          b_e_d
0x0153   œ          g_o_
0x025C   ɜ          b_u_st
0x025E   ɞ          b_u_t
0x028C   ʌ          r_u_n
0x0254   ɔ          _o_besus
0x00E6   æ          c_a_t
0x0250   ɐ          c_u_t
0x0061   a          p_a_ter
0x0276   ɶ          ?
0x0251   ɑ          h_o_t
0x0252   ɒ          c_ou_gh

supported consonants: 
unicode  IPA glyph  pronuciation    
p         p	        <b>p</b>ater, s<b>p</b>in
b         b	        <b>b</b>ut, <b>b</b>utt
t         t	        s<b>t</b>op
d         d	        <b>d</b>i<b>d</b>, <b>d</b>o	
0x0288    ʈ         <b>t</b>ime
0x0256    ɖ         <b>d</b>ine
c         c	        n/a	      
0x025F    ɟ         <b>g</b>eese
k         k         s<b>c</b>an, ta<b>k</b>e	
g         ɡ	        <b>g</b>o, <b>g</b>et
q         q	        n/a
0x0262    ɢ         <b>g</b>audy
0x02A1    ʡ         epiglotal stop
*** start of second row
m         m	        <b>m</b>an, le<b>m</b>on
0x0271    ɱ         sy<b>m</b>phony
n         n         <b>n</b>emo, <b>n</b>o
0x0273    ɳ         ca<b>ny</b>on
0x0272    ɲ         n/a
0x014b    ŋ         si<b>ng</b>er, ri<b>ng</b>
0x0274    ɴ         n/a  
*** start of third row
0x0299    ʙ         n/a
r         r         <b>r</b>ed, t<b>r</b>y
0x0280    ʀ         <b>r</b>ot (german)
*** start of fourth row
0x2c71    ⱱ         n/a
0x027e    ɾ         <b>r</b>oma, be<b>tt</b>er
0x027d    ɽ         <b>r</b>iem (dutch)
*** start of fifth row
0x0278    ɸ         n/a
0x03B2    β         a<b>b</b>er (german)
f         f	        <b>f</b>ool, enou<b>gh</b>
v         v	        <b>v</b>oice
0x03B8    θ         <b>th</b>ing
0x00F0    ð         <b>th</b>is
s         s	        <b>s</b>ee, pa<b>ss</b>
z         z	        <b>z</b>oo, ro<b>s</b>es
0x0283    ʃ	        <b>sh</b>e, cra<b>sh</b>
0x0292    ʒ	        vi<b>si</b>on, trea<b>s</b>ure
0x0282    ʂ         n/a
0x0290    ʐ         n/a
0x00E7    ç         <b>h</b>uge
0x029D    ʝ         <b>J</b>acke (german)
x         x	        lo<b>ch</b>
0x0263    ɣ         damali<b>g</b>e (german)
0x03C7    χ         Da<b>ch</b> (german)
0x0281    ʁ         <b>R</b>ost (german)
0x0127    ħ         <b>h</b>at
0x02A2    ʢ         n/a
h         h	        <b>h</b>onor, <b>h</b>am
0x0266    ɦ         a<b>h</b>ead
*** start of sixth row:
0x026D    ɭ         n/a
0x026E    ɮ         n/a
*** start of seventh row:
0x028B    ʋ         <b>w</b>ang (dutch)
0x0279    ɹ         <b>R</b>ebe (german)
0x027B    ɻ         <b>r</b>un, ve<b>r</b>y
j         j	        <b>j</b>ucundus, <b>y</b>es
0x0270    ɰ         e<b>m</b>phasis
*** start of eight row:
0x026B    ɫ	        pu<b>ll</b>
l         l	        <b>l</b>udus, <b>l</b>eft
0x026D    ɭ         n/a
0x028E    ʎ         mi<b>lli</b>on
0x029F    ʟ         mi<b>l</b>k
*** start of ninth row:
0X028D    ʍ         <b>wh</b>ine
w         w	        <b>v</b>olvo    <b>w</b>e
0X0265    ɥ         n/a
0X0295    ʕ         Mutter<b>r</b> (german)
0x029C    ʜ         n/a
0X0294    ʔ         uh-oh (glottal stop)
0X0291    ʑ         vi<b>si</b>on
0X0255    ɕ         <b>sh</b>ip
0X027A    ɺ         n/a
0X0267    ɧ         n/a
0x02A4    ʤ         lar<b>ge</b>, <b>j</b>ust
0x02A7    ʧ         <b>ch</b>air, pic<b>t</b>ure











































*/