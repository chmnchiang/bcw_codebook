colo torte
syn on
se cin ai ar sm nu ru is
se mouse=a bs=2 ww+=<,>,[,] so=6 ts=4 sw=4 ttm=100
se makeprg=g++\ -Wall\ -Wshadow\ -O2\ -o\ %<\ %
au BufNewFile *.cpp 0r ~/default.cpp

map <F7> <ESC>:wa<CR>:make!<CR>
imap <F7> <ESC>:wa<CR>:make!<CR>
map <C-F7> <ESC>:tabe %<.in<CR>
map <F8> :copen <CR>
map <S-F8> :cclose <CR>
map <F9> :!./%< <CR>
map <C-F9> :!./%< < %<.in <CR>

