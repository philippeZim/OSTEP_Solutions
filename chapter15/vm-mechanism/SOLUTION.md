./relocation.py -s 1

Base   : 0x0000363c (decimal 13884)
Limit  : 290

Virtual Address Trace
  VA  0: 0x0000030e (decimal:  782) --> segmentation violation
  VA  1: 0x00000105 (decimal:  261) --> PA 13884+261 = 14145
  VA  2: 0x000001fb (decimal:  507) --> segmentation violation
  VA  3: 0x000001cc (decimal:  460) --> segmentation violation
  VA  4: 0x0000029b (decimal:  667) --> segmentation violation

./relocation.py -s 2

Base   : 0x00003ca9 (decimal 15529)
Limit  : 500

Virtual Address Trace
  VA  0: 0x00000039 (decimal:   57) --> PA 15586
  VA  1: 0x00000056 (decimal:   86) --> PA 15615
  VA  2: 0x00000357 (decimal:  855) --> segmentation violation
  VA  3: 0x000002f1 (decimal:  753) --> segmentation violation
  VA  4: 0x000002ad (decimal:  685) --> segmentation violation

./relocation.py -s 3

Base   : 0x000022d4 (decimal 8916)
Limit  : 316

Virtual Address Trace
  VA  0: 0x0000017a (decimal:  378) --> segmentation violation
  VA  1: 0x0000026a (decimal:  618) --> segmentation violation
  VA  2: 0x00000280 (decimal:  640) --> segmentation violation
  VA  3: 0x00000043 (decimal:   67) --> PA 8983
  VA  4: 0x0000000d (decimal:   13) --> PA 8929

./relocation.py -s 0 -n 10 -l 930

./relocation.py -s 1 -n 10 -l 100 -b 16284