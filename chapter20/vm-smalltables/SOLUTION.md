./paging-multilevel-translate.py -n 1 -s 0

PDBR: 108  (decimal) [This means the page directory is held in this page]

Virtual Address 611c: Translates To What Physical Address (And Fetches what Value)? Or Fault?

Virtual Address: 0110 0001 0001 1100
(5 for the offset, 10 for the VPN)
VPN: 11 0000 1000
Offset: 1 1100

PDIndex: 1 1000 (24)

page 108:83fee0da7fd47febbe9ed5ade4ac90d692d8c1f89fe1ede9a1e8c7c2a9d1dbff

PDE: 0xa1, 1010 0001 -> valid

PTEAddr:
010 0001 << 5 + 0 1000

PT:
page  33:7f7f7f7f7f7f7f7fb57f9d7f7f7f7f7f7f7f7f7f7f7f7f7f7f7ff6b17f7f7f7f

PTE: (PFN)
0xb5 -> 1011 0101 -> valid

Physical addr: (PFN | Offset)
11 0101 | 1 1100

0x6bc

11 0101 (53)
1 1100 (28)

page  53:0f0c18090e121c0f081713071c1e191b09161b150e030d121c1d0e1a08181100

Value:
0x08 (8)

----------------------------

./paging-multilevel-translate.py -n 1 -s 1

Virtual Addr:
0x6c74
0110 1100 0111 0100

Offset:
1 0100
VPN:
110 1100 011

PDIndex:
110 11 (27)

PD:
page  17:daf7f2a896c59d94c8b97fc498e57f7fd3a1828fa6fbbff07f84d2a08880c992

PDE:
0xa0
1010 0000 -> valid

10 0000 << 5 + 00 011
100 0000 0011

PTAdrr 10 0000 (32):
page  32:7f7f7fe17f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7fdb7f7f7f
e1 1110 0001 -> valid
110 0001 (97) -> PTE

PTE << 7 | Offset

110 0001 (97)
1 0100 (20)

Physical addr:
1100 0011 0100
0xc34

page  97:0f0d14180200190d17000d16071d1b0000101d0b060d00060d0f0707060e0800

Value: 06 -> (6)

--------------------------

Virtual Address 0x7570

0111 0101 0111 0000

VPN:
111 0101 011
Offset:
1 0000

PDIndex = erste 5 bit der VPN
11101 (29)

PDBR (gegeben): 122 decimal

page 122:82cdad9dabe87faf7fd37ff892cabeaa897fe999bb7fc2e0d7b8df7fdeb38a7f

0xb3 : PDE
1011 0011 -> Valid


PTAddr = PDE << Shift + VPN(letzte 5 bit)
110 0110 1011

0x66b

page  51:7f7f7f7f7fc97f7f7f7f7f7f7f7f7f7f7f7f7f857f7f7f7f7f7f7f7f7f7f7f7f

0x7f 0111 1111 -> invalid
