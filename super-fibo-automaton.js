// This text is to be put at http://web.cs.ucdavis.edu/~doty/automata/ to simulate the automaton.

// States and alphabet
states = { s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12 }
input_alphabet = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q }

// Initial and final states
start_state = s0
accept_states = {s0, s6, s10}

// Transition function
delta =
	s0,0 -> s0;
	s0,1 -> s1;
	s0,2 -> s2;
	s0,3 -> s3;
	s0,4 -> s0;
	s0,5 -> s1;
	s0,6 -> s12;
	s0,7 -> s3;
	s0,8 -> s0;
	s0,9 -> s3;
	s0,a -> s0;
	s0,b -> s1;
	s0,c -> s12;
	s0,d -> s3;
	s0,e -> s0;
	s0,f -> s12;
	s0,g -> s12;
	s0,h -> s3;
	s0,i -> s12;
	s0,j -> s3;
	s0,k -> s0;
	s0,l -> s12;
	s0,m -> s12;
	s0,n -> s3;
	s0,o -> s12;
	s0,p -> s12;
	s0,q -> s12;

	s1,0 -> s4;
	s1,1 -> s12;
	s1,2 -> s12;
	s1,3 -> s5;
	s1,4 -> s4;
	s1,5 -> s12;
	s1,6 -> s6;
	s1,7 -> s5;
	s1,8 -> s4;
	s1,9 -> s5;
	s1,a -> s4;
	s1,b -> s12;
	s1,c -> s6;
	s1,d -> s5;
	s1,e -> s4;
	s1,f -> s7;
	s1,g -> s6;
	s1,h -> s5;
	s1,i -> s6;
	s1,j -> s5;
	s1,k -> s4;
	s1,l -> s7;
	s1,m -> s6;
	s1,n -> s5;
	s1,o -> s12;
	s1,p -> s7;
	s1,q -> s6;

	s2,0 -> s12;
	s2,1 -> s12;
	s2,2 -> s12;
	s2,3 -> s12;
	s2,4 -> s12;
	s2,5 -> s12;
	s2,6 -> s12;
	s2,7 -> s12;
	s2,8 -> s12;
	s2,9 -> s12;
	s2,a -> s12;
	s2,b -> s12;
	s2,c -> s12;
	s2,d -> s12;
	s2,e -> s12;
	s2,f -> s8;
	s2,g -> s12;
	s2,h -> s12;
	s2,i -> s12;
	s2,j -> s12;
	s2,k -> s12;
	s2,l -> s8;
	s2,m -> s12;
	s2,n -> s12;
	s2,o -> s9;
	s2,p -> s8;
	s2,q -> s12;

	s3,0 -> s12;
	s3,1 -> s12;
	s3,2 -> s10;
	s3,3 -> s12;
	s3,4 -> s12;
	s3,5 -> s12;
	s3,6 -> s12;
	s3,7 -> s12;
	s3,8 -> s12;
	s3,9 -> s12;
	s3,a -> s12;
	s3,b -> s12;
	s3,c -> s12;
	s3,d -> s12;
	s3,e -> s12;
	s3,f -> s12;
	s3,g -> s12;
	s3,h -> s12;
	s3,i -> s12;
	s3,j -> s12;
	s3,k -> s12;
	s3,l -> s12;
	s3,m -> s12;
	s3,n -> s12;
	s3,o -> s12;
	s3,p -> s12;
	s3,q -> s12;

	s4,0 -> s12;
	s4,1 -> s12;
	s4,2 -> s12;
	s4,3 -> s12;
	s4,4 -> s12;
	s4,5 -> s12;
	s4,6 -> s12;
	s4,7 -> s12;
	s4,8 -> s12;
	s4,9 -> s12;
	s4,a -> s12;
	s4,b -> s12;
	s4,c -> s12;
	s4,d -> s12;
	s4,e -> s12;
	s4,f -> s12;
	s4,g -> s12;
	s4,h -> s12;
	s4,i -> s12;
	s4,j -> s12;
	s4,k -> s12;
	s4,l -> s12;
	s4,m -> s12;
	s4,n -> s12;
	s4,o -> s8;
	s4,p -> s12;
	s4,q -> s12;

	s5,0 -> s12;
	s5,1 -> s12;
	s5,2 -> s12;
	s5,3 -> s4;
	s5,4 -> s12;
	s5,5 -> s12;
	s5,6 -> s5;
	s5,7 -> s4;
	s5,8 -> s12;
	s5,9 -> s4;
	s5,a -> s12;
	s5,b -> s12;
	s5,c -> s5;
	s5,d -> s4;
	s5,e -> s12;
	s5,f -> s6;
	s5,g -> s5;
	s5,h -> s4;
	s5,i -> s5;
	s5,j -> s4;
	s5,k -> s12;
	s5,l -> s6;
	s5,m -> s5;
	s5,n -> s4;
	s5,o -> s7;
	s5,p -> s6;
	s5,q -> s5;

	s6,0 -> 	s1;
	s6,1 -> 	s2;
	s6,2 -> 	s12;
	s6,3 -> 	s0;
	s6,4 -> 	s1;
	s6,5 -> 	s2;
	s6,6 -> 	s3;
	s6,7 -> 	s0;
	s6,8 -> 	s1;
	s6,9 -> 	s0;
	s6,a ->	s1;
	s6,b ->	s2;
	s6,c ->	s3;
	s6,d ->	s0;
	s6,e ->	s1;
	s6,f ->	s12;
	s6,g ->	s3;
	s6,h ->	s0;
	s6,i ->	s3;
	s6,j ->	s0;
	s6,k ->	s1;
	s6,l ->	s12;
	s6,m ->	s3;
	s6,n ->	s0;
	s6,o ->	s12;
	s6,p ->	s12;
	s6,q ->	s3;

	s7,0 -> 	s12;
	s7,1 -> 	s10;
	s7,2 -> 	s11;
	s7,3 -> 	s12;
	s7,4 -> 	s12;
	s7,5 -> 	s10;
	s7,6 -> 	s12;
	s7,7 -> 	s12;
	s7,8 -> 	s12;
	s7,9 -> 	s12;
	s7,a ->	s12;
	s7,b ->	s10;
	s7,c ->	s12;
	s7,d ->	s12;
	s7,e ->	s12;
	s7,f ->	s12;
	s7,g ->	s12;
	s7,h ->	s12;
	s7,i ->	s12;
	s7,j ->	s12;
	s7,k ->	s12;
	s7,l ->	s12;
	s7,m ->	s12;
	s7,n ->	s12;
	s7,o ->	s12;
	s7,p ->	s12;
	s7,q ->	s12;

	s8,0 -> 	s12;
	s8,1 -> 	s12;
	s8,2 -> 	s12;
	s8,3 -> 	s12;
	s8,4 -> 	s12;
	s8,5 -> 	s12;
	s8,6 -> 	s4;
	s8,7 -> 	s12;
	s8,8 -> 	s12;
	s8,9 -> 	s12;
	s8,a ->	s12;
	s8,b ->	s12;
	s8,c ->	s4;
	s8,d ->	s12;
	s8,e ->	s12;
	s8,f ->	s5;
	s8,g ->	s4;
	s8,h ->	s12;
	s8,i ->	s4;
	s8,j ->	s12;
	s8,k ->	s12;
	s8,l ->	s5;
	s8,m ->	s4;
	s8,n ->	s12;
	s8,o ->	s6;
	s8,p ->	s5;
	s8,q ->	s4;

	s9,0 -> 	s2;
	s9,1 -> 	s12;
	s9,2 -> 	s12;
	s9,3 -> 	s1;
	s9,4 -> 	s2;
	s9,5 -> 	s12;
	s9,6 -> 	s0;
	s9,7 -> 	s1;
	s9,8 -> 	s2;
	s9,9 -> 	s1;
	s9,a ->	s2;
	s9,b ->	s12;
	s9,c ->	s0;
	s9,d ->	s1;
	s9,e ->	s2;
	s9,f ->	s3;
	s9,g ->	s0;
	s9,h ->	s1;
	s9,i ->	s0;
	s9,j ->	s1;
	s9,k ->	s2;
	s9,l ->	s3;
	s9,m ->	s0;
	s9,n ->	s1;
	s9,o ->	s12;
	s9,p ->	s3;
	s9,q ->	s0;

	s10,0 -> 	s3;
	s10,1 -> 	s0;
	s10,2 -> 	s1;
	s10,3 -> 	s12;
	s10,4 -> 	s3;
	s10,5 -> 	s0;
	s10,6 -> 	s12;
	s10,7 -> 	s12;
	s10,8 -> 	s3;
	s10,9 -> 	s12;
	s10,a ->	s3;
	s10,b ->	s0;
	s10,c ->	s12;
	s10,d ->	s12;
	s10,e ->	s3;
	s10,f ->	s12;
	s10,g ->	s12;
	s10,h ->	s12;
	s10,i ->	s12;
	s10,j ->	s12;
	s10,k ->	s3;
	s10,l ->	s12;
	s10,m ->	s12;
	s10,n ->	s12;
	s10,o ->	s12;
	s10,p ->	s12;
	s10,q ->	s12;

	s11,0 -> 	s5;
	s11,1 -> 	s4;
	s11,2 -> 	s12;
	s11,3 -> 	s6;
	s11,4 -> 	s5;
	s11,5 -> 	s4;
	s11,6 -> 	s7;
	s11,7 -> 	s6;
	s11,8 -> 	s5;
	s11,9 -> 	s6;
	s11,a ->	s5;
	s11,b ->	s4;
	s11,c ->	s7;
	s11,d ->	s6;
	s11,e ->	s5;
	s11,f ->	s12;
	s11,g ->	s7;
	s11,h ->	s6;
	s11,i ->	s7;
	s11,j ->	s6;
	s11,k ->	s5;
	s11,l ->	s12;
	s11,m ->	s7;
	s11,n ->	s6;
	s11,o ->	s12;
	s11,p ->	s12;
	s11,q ->	s7;

	s12,0 -> 	s12;
	s12,1 -> 	s12;
	s12,2 -> 	s12;
	s12,3 -> 	s12;
	s12,4 -> 	s12;
	s12,5 -> 	s12;
	s12,6 -> 	s12;
	s12,7 -> 	s12;
	s12,8 -> 	s12;
	s12,9 -> 	s12;
	s12,a ->	s12;
	s12,b ->	s12;
	s12,c ->	s12;
	s12,d ->	s12;
	s12,e ->	s12;
	s12,f ->	s12;
	s12,g ->	s12;
	s12,h ->	s12;
	s12,i ->	s12;
	s12,j ->	s12;
	s12,k ->	s12;
	s12,l ->	s12;
	s12,m ->	s12;
	s12,n ->	s12;
	s12,o ->	s12;
	s12,p ->	s12;
	s12,q ->	s12;
  
