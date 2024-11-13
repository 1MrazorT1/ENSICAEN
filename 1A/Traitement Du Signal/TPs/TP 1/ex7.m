a = [3+4i 5+9i -3-4i -5-9i 3-4i 5-9i -3+4i -5+9i];

module=@(x) abs(x);
phase=@(x) angle(x);
conjugue=@(x) conj(x);

module_values=module(a);
phase_values=phase(a);
conjugue_values=conj(a);

disp(module_values);
disp(phase_values);
disp(conjugue_values);