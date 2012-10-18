vim配置

set nu ru nobk nowrap si mouse=a sw=4 sts=4 ts=4
set hlsearch incsearch
syntax on
filetype plugin on
filetype plugin indent on
set foldmethod=marker

nmap <C-A> ggVG
vmap <C-C> "+y

map <F12> :!g++ -g % -o %< -O2 -Wall <CR>
autocmd BufNewFile *.cpp 0r ~/Templates/lcCpp.cpp
autocmd FileType c,cpp :set ci
autocmd FileType c,cpp :map <F9> :make %< <CR>
autocmd FileType c,cpp :map <F5> :!./%< <CR>
autocmd FileType c,cpp :map <F8> :!./%< < %<.in <CR>

autocmd FileType java :set makeprg=javac\ % errorformat=%A%f:%l:\ %m,%-Z%p^,%-C%.%#
autocmd FileType java :map <F9> :make <CR>
autocmd FileType java :map <F5> :!java %< <CR>
autocmd FileType java :map <F8> :!java %< < %<.in <CR>

map <F3> : vnew %<.in<CR>
map <F4> : !gedit %<CR>

export CXXFLAGS="-Wall -O2"

