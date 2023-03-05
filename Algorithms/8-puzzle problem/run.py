from algorithm import PuzzleBoard


if __name__ == "__main__":
    times, st, avg_st = [], [], []
    for i in range(20):
        puzzle = PuzzleBoard()

        try:
            t, states, avg_states = puzzle.find_ucs_solution(verbose=False)
        except RuntimeError:
            print("WARNING: Time was exceeded :(")
        else:
            print(f"Try: {i}, Time: {t}, Total states: {states}, Max States: {avg_states}")

            times.append(t)
            st.append(states)
            avg_st.append(avg_states)

    print(times)
    print(st)
    print(avg_st)
    print(f"Average time: {sum(times) / len(times)}")
    print(f"Average states: {sum(st) / len(st)}")
    print(f"Average avg_st: {sum(avg_st) / len(avg_st)}")
