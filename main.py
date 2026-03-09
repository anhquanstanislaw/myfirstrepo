"""
Hand landmark tracking using Google's MediaPipe library.

MediaPipe Hands detects 21 landmarks per hand. Each landmark carries
three values: x, y (normalized to [0, 1] by the image width/height)
and z (depth, relative to the wrist).

Landmark indices
----------------
0  - WRIST              (the conventional "constant / reference" point)
1  - THUMB_CMC
2  - THUMB_MCP
3  - THUMB_IP
4  - THUMB_TIP
5  - INDEX_FINGER_MCP
6  - INDEX_FINGER_PIP
7  - INDEX_FINGER_DIP
8  - INDEX_FINGER_TIP
9  - MIDDLE_FINGER_MCP
10 - MIDDLE_FINGER_PIP
11 - MIDDLE_FINGER_DIP
12 - MIDDLE_FINGER_TIP
13 - RING_FINGER_MCP
14 - RING_FINGER_PIP
15 - RING_FINGER_DIP
16 - RING_FINGER_TIP
17 - PINKY_MCP
18 - PINKY_PIP
19 - PINKY_DIP
20 - PINKY_TIP
"""

import cv2
import mediapipe as mp


# ---------------------------------------------------------------------------
# Normalisation helper
# ---------------------------------------------------------------------------

def normalize_landmarks(landmarks, reference_index=0):
    """Return a list of (x, y, z) tuples normalized to a reference landmark.

    The function subtracts the coordinates of the chosen reference point from
    every landmark so that the reference point becomes the origin (0, 0, 0).
    This makes the representation independent of where the hand is positioned
    inside the frame.

    Parameters
    ----------
    landmarks : list of mediapipe.framework.formats.landmark_pb2.NormalizedLandmark
        The 21-element list of hand landmarks produced by MediaPipe.
        Each element has ``.x``, ``.y`` and ``.z`` attributes.

        Hint: you obtain this list from
        ``results.multi_hand_landmarks[hand_index].landmark``

    reference_index : int, optional
        Index of the landmark that acts as the fixed / constant reference
        point.  Defaults to ``0`` (the **wrist**), which is the most common
        choice because the wrist is the stable "root" of the hand skeleton.

        Other sensible choices:
        * ``9``  – middle-finger MCP (palm centre proxy)
        * ``5``  – index-finger MCP

    Returns
    -------
    list of tuple[float, float, float]
        21 ``(x, y, z)`` tuples where every coordinate has been shifted so
        that ``landmarks[reference_index]`` maps to ``(0.0, 0.0, 0.0)``.

    Examples
    --------
    >>> # After running MediaPipe on a frame:
    >>> hand_landmarks = results.multi_hand_landmarks[0].landmark
    >>> normalized = normalize_landmarks(hand_landmarks, reference_index=0)
    >>> print(normalized[0])   # should be (0.0, 0.0, 0.0) – the wrist
    """
    ref = landmarks[reference_index]
    ref_x, ref_y, ref_z = ref.x, ref.y, ref.z

    normalized = [
        (lm.x - ref_x, lm.y - ref_y, lm.z - ref_z)
        for lm in landmarks
    ]
    return normalized


# ---------------------------------------------------------------------------
# Main tracking loop
# ---------------------------------------------------------------------------

def main():
    mp_hands = mp.solutions.hands
    mp_draw = mp.solutions.drawing_utils

    cap = cv2.VideoCapture(0)

    with mp_hands.Hands(
        static_image_mode=False,
        max_num_hands=2,
        min_detection_confidence=0.5,
        min_tracking_confidence=0.5,
    ) as hands:

        while cap.isOpened():
            success, frame = cap.read()
            if not success:
                break

            # MediaPipe expects RGB input
            rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            results = hands.process(rgb_frame)

            if results.multi_hand_landmarks:
                for hand_landmarks in results.multi_hand_landmarks:
                    # Draw the 21 landmarks and connections on the frame
                    mp_draw.draw_landmarks(
                        frame,
                        hand_landmarks,
                        mp_hands.HAND_CONNECTIONS,
                    )

                    # Normalize all 21 coordinates relative to the wrist (index 0)
                    normalized = normalize_landmarks(
                        hand_landmarks.landmark,
                        reference_index=0,
                    )

                    # `normalized` is now a list of 21 (x, y, z) tuples where
                    # the wrist sits at the origin (0, 0, 0).
                    print("Normalized landmarks:", normalized)

            cv2.imshow("Hand Tracking", frame)
            if cv2.waitKey(1) & 0xFF == ord("q"):
                break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
