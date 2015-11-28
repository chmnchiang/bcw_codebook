#! /usr/bin/env python3

import os
from os.path import basename

order_list = [
    'Basic',
    'Data_Structure',
    'Graph',
    'Math',
    'Geometry',
    'Stringology',
    'Problems'
]

def un(s):
    return s.replace('_', ' ')

def eq(a, b):
    return a.lower() == b.lower()

with open('pdf/codebook_gen.tex', 'w') as f:
    for title in order_list:
        f.write('\\section{%s}\n' % un(title))
        for root, dirs, files in os.walk('codes/%s' % title):
            # print(root, dirs, files)
            base = basename(root)
            if files:
                eq_files = list(filter(lambda x: eq(base, x.split('.')[0]),
                                  files))
                if eq_files:
                    fn = ' '.join([x[0].upper() + x[1:] for x in base.split('_')])
                    f.write('\\subsection{%s}\n' % fn)
                    f.write('\\lstinputlisting{../%s/%s}\n' % (root, eq_files[0]))
                    continue
