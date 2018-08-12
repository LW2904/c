/*
 * TODO: https://www.systutorials.com/docs/linux/man/3-xcb_get_property/
 */

/*
 * Prints the WM_NAME property of the window.
 *
 */
void my_example(xcb_connection_t *c, xcb_window_t window) {
    xcb_get_property_cookie_t cookie;
    xcb_get_property_reply_t *reply;

    /* These atoms are predefined in the X11 protocol. */
    xcb_atom_t property = XCB_ATOM_WM_NAME;
    xcb_atom_t type = XCB_ATOM_STRING;

    // TODO: a reasonable long_length for WM_NAME?
    cookie = xcb_get_property(c, 0, window, property, type, 0, 0);
    if ((reply = xcb_get_property_reply(c, cookie, NULL))) {
        int len = xcb_get_property_value_length(reply);
        if (len == 0) {
            printf("TODO\n");
            free(reply);
            return;
        }
        printf("WM_NAME is %.*s\n", len,
               (char*)xcb_get_property_value(reply));
    }
    free(reply);
}