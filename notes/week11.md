"C++ does not hold your hand. It'll happily load the gun and let you shoot yourself" - Dr. Sundberg

```cpsl
const N := 100;

type A : array[0..N] of integer;

procedure merge(ref a : A; var size :integer);
var front, back : A;
    halfPlusOne, i, j, cur : integer;
begin
    for i := 0 to size / 2
    begin
        front[i] = a[i];
    end
    merge(front, size / 2);
    halfPlusOne := size / 2 + 1
    for i := halfPlusOne to size
    begin
        back[i - halfPlusOne] = a[i];
    end
    merge(back, size - halfPlusOne);

    i := 0;
    j := 0;
    cur := 0;
    while(i < size / 2 && j < size - halfPlusOne)
    begin
        if(front[i] < back[j]) then
            a[cur] = front[i];
            i := succ(i);
        else
            a[cur] = back[j];
            j := succ(j);
        end;
        cur := succ(cur);
    end

    $add the rest of the unfinished one
end
```