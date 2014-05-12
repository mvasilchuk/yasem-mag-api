(function(){
    console.log('Font fix!');
    var link = document.createElement('link');
    link.setAttribute('rel', 'stylesheet');
    link.setAttribute('type', 'text/css');
    link.setAttribute('href', ':/mag/fixes/fontfix.css');
    document.getElementsByTagName('head')[0].appendChild(link);
})();

