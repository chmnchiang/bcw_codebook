colo torte
syn on
set ts=4 sw=4
set cin ai ar sm nu ru
set mouse=a
set bs=2
set ww+=<,>,[,]
set so=6

set makeprg=g++\ -Wall\ -Wshadow\ -O2\ -o\ %<\ %
au BufNewFile *.cpp 0r ~/default.cpp

map <F8> <ESC>:wa<CR>:make!<CR>
imap <F8> <ESC>:wa<CR>:make!<CR>
map <F9> :!%< <CR>
map <C-F9> :!%< < %<.in <CR>
map <F10> :copen <CR>
map <S-F10> :cclose <CR>
