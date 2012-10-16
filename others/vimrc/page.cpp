set nu ru nobk nowrap si mouse=a
set tabstop=4 shiftwidth=4 softtabstop=4 hlsearch incsearch
syntax on
filetype plugin on
filetype plugin indent on

autocmd FileType c,cpp : set cindent
autocmd FileType java : compiler javac
autocmd FileType java : map <F9> : make % <cr>
autocmd FileType c,cpp : map <F9> : make %< <cr>
autocmd FileType python : map <F9> : !python % <cr>
autocmd FileType c,cpp,python : map <F8> : !./%< < %<.in<cr>
autocmd FileType c,cpp,python : map <F5> : !./%< <cr>
autocmd FileType java : map<F8> : !java %< < %<.in <cr>
autocmd FileType java : map<F5> : !java %< <cr>

map <F12> : !rm %< <cr> : !rm %<.in <cr>
map <F3> : new %<.in<cr>
nmap <C-A> ggVG
vmap <C-C> : w !pbcopy<cr>

