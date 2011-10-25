function selAll(e) {
 	var a = document.getElementsByName('id[]');
    var l = a.length; while(l--) a[l].checked=e.checked;
}