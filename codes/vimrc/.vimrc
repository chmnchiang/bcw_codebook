colo torte
syn on
set ts=4 sw=4
set cin ai ar sm nu ru
set mouse=a
set bs=2
set ww+=<,>,[,]

set makeprg=g++\ -Wall\ -Wshadow\ -O2\ -o\ %<\ %

map <F8> :wa<CR>:make!<CR>
map <F9> :!./%< <CR>
map <C-F9> :!./%< < %<.in <CR>
map <F10> :copen <CR>
map <S-F10> :cclose <CR>

