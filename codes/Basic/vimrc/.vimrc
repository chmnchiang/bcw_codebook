colo torte
syn on
se cin ai ar sm nu ru mouse=a bs=2 ww+=<,>,[,] so=6 ts=4 sw=4
se makeprg=g++\ -Wall\ -Wshadow\ -O2\ -o\ %<\ %
au BufNewFile *.cpp 0r ~/default.cpp

map <F8> <ESC>:wa<CR>:make!<CR>
imap <F8> <ESC>:wa<CR>:make!<CR>
map <F9> :!%< <CR>
map <C-F9> :!%< < %<.in <CR>
map <F10> :copen <CR>
map <S-F10> :cclose <CR>
